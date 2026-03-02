// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_MINER_H
#define RXB_MINER_H

#include <primitives/block.h>
#include <txmempool.h>
#include <chainparams.h>
#include <validation.h>
#include <consensus/validation.h>
#include <net.h>
#include <wallet/wallet.h>
#include <rpc/server.h>
#include <thread>
#include <atomic>
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <boost/optional.hpp>

// RXB mining constants
static const bool DEFAULT_PRINTPRIORITY = false;
static const CAmount RXB_DEFAULT_BLOCK_MIN_TX_FEE = 1000; // in satoshis (unique name)

struct CBlockTemplate
{
    CBlock block;
    std::vector<CAmount> vTxFees;
    std::vector<int64_t> vTxSigOpsCost;
    std::vector<unsigned char> vchCoinbaseCommitment;
};

// Container for tracking updates to ancestor feerate as we include (parent)
// transactions in a block
struct CTxMemPoolModifiedEntry {
    explicit CTxMemPoolModifiedEntry(CTxMemPool::txiter entry)
    {
        iter = entry;
        nSizeWithAncestors = entry->GetSizeWithAncestors();
        nModFeesWithAncestors = entry->GetModFeesWithAncestors();
        nSigOpCostWithAncestors = entry->GetSigOpCostWithAncestors();
    }

    int64_t GetModifiedFee() const { return iter->GetModifiedFee(); }
    uint64_t GetSizeWithAncestors() const { return nSizeWithAncestors; }
    CAmount GetModFeesWithAncestors() const { return nModFeesWithAncestors; }
    size_t GetTxSize() const { return iter->GetTxSize(); }
    const CTransaction& GetTx() const { return iter->GetTx(); }

    CTxMemPool::txiter iter;
    uint64_t nSizeWithAncestors;
    CAmount nModFeesWithAncestors;
    int64_t nSigOpCostWithAncestors;
};

/** Comparator for CTxMemPool::txiter objects. */
struct CompareCTxMemPoolIter {
    bool operator()(const CTxMemPool::txiter& a, const CTxMemPool::txiter& b) const
    {
        return &(*a) < &(*b);
    }
};

struct modifiedentry_iter {
    typedef CTxMemPool::txiter result_type;
    result_type operator() (const CTxMemPoolModifiedEntry &entry) const
    {
        return entry.iter;
    }
};

// A comparator that sorts transactions based on number of ancestors.
struct CompareTxIterByAncestorCount {
    bool operator()(const CTxMemPool::txiter &a, const CTxMemPool::txiter &b) const
    {
        if (a->GetCountWithAncestors() != b->GetCountWithAncestors())
            return a->GetCountWithAncestors() < b->GetCountWithAncestors();
        return CTxMemPool::CompareIteratorByHash()(a, b);
    }
};

// NOTE: CompareTxMemPoolEntryByAncestorFee and ancestor_score are already defined in txmempool.h
// We use those definitions instead of redefining them here

typedef boost::multi_index_container<
    CTxMemPoolModifiedEntry,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            modifiedentry_iter,
            CompareCTxMemPoolIter
        >,
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<ancestor_score>,
            boost::multi_index::identity<CTxMemPoolModifiedEntry>,
            CompareTxMemPoolEntryByAncestorFee
        >
    >
> indexed_modified_transaction_set;

typedef indexed_modified_transaction_set::nth_index<0>::type::iterator modtxiter;
typedef indexed_modified_transaction_set::index<ancestor_score>::type::iterator modtxscoreiter;

struct update_for_parent_inclusion
{
    explicit update_for_parent_inclusion(CTxMemPool::txiter it) : iter(it) {}

    void operator() (CTxMemPoolModifiedEntry &e)
    {
        e.nModFeesWithAncestors -= iter->GetFee();
        e.nSizeWithAncestors -= iter->GetTxSize();
        e.nSigOpCostWithAncestors -= iter->GetSigOpCost();
    }

    CTxMemPool::txiter iter;
};

/** Generate a new block, without valid proof-of-work */
class BlockAssembler
{
private:
    std::unique_ptr<CBlockTemplate> pblocktemplate;
    CBlock* pblock;

    bool fIncludeWitness;
    unsigned int nBlockMaxWeight;
    CFeeRate blockMinFeeRate;

    uint64_t nBlockWeight;
    uint64_t nBlockTx;
    uint64_t nBlockSigOpsCost;
    CAmount nFees;
    CTxMemPool::setEntries inBlock;

    int nHeight;
    int64_t nLockTimeCutoff;
    const CChainParams& chainparams;
    const CTxMemPool& m_mempool;

public:
    struct Options {
        Options();
        size_t nBlockMaxWeight;
        CFeeRate blockMinFeeRate;
    };

    explicit BlockAssembler(const CTxMemPool& mempool, const CChainParams& params);
    explicit BlockAssembler(const CTxMemPool& mempool, const CChainParams& params, const Options& options);

    /** Construct a new block template with coinbase to scriptPubKeyIn */
    std::unique_ptr<CBlockTemplate> CreateNewBlock(const CScript& scriptPubKeyIn);

    static boost::optional<int64_t> m_last_block_num_txs;
    static boost::optional<int64_t> m_last_block_weight;

private:
    void resetBlock();
    void AddToBlock(CTxMemPool::txiter iter);
    void addPackageTxs(int& nPackagesSelected, int& nDescendantsUpdated);
    void onlyUnconfirmed(CTxMemPool::setEntries& testSet);
    bool TestPackage(uint64_t packageSize, int64_t packageSigOpsCost) const;
    bool TestPackageTransactions(const CTxMemPool::setEntries& package);
    bool SkipMapTxEntry(CTxMemPool::txiter it, indexed_modified_transaction_set& mapModifiedTx, CTxMemPool::setEntries& failedTx);
    void SortForBlock(const CTxMemPool::setEntries& package, std::vector<CTxMemPool::txiter>& sortedEntries);
    int UpdatePackagesForAdded(const CTxMemPool::setEntries& alreadyAdded, indexed_modified_transaction_set& mapModifiedTx);
};

/**
 * RXB Miner - Solo mining implementation
 */
class RXBMiner {
private:
    std::atomic<bool> fMining;
    std::vector<std::thread> miningThreads;
    CAmount miningReward;
    std::string miningAddress;
    CConnman* connman;
    std::mutex cs_miner;
    std::condition_variable cv_miner;
    std::queue<std::pair<uint256, CBlock> > minedBlocksQueue;
    
    std::atomic<uint64_t> hashCount;
    std::atomic<uint64_t> blockCount;
    std::atomic<double> hashRate;
    std::atomic<bool> fStopMining;
    
public:
    RXBMiner(CConnman* connman = nullptr);
    ~RXBMiner();
    
    bool StartMining(const std::string& address, int nThreads = 1);
    void StopMining();
    bool IsMining() const { return fMining.load(); }
    void GetMiningStats(uint64_t& hashes, uint64_t& blocks, double& rate);
    std::unique_ptr<CBlockTemplate> CreateNewBlock(const CScript& scriptPubKey);
    bool MineBlock(CBlock& block, const CChainParams& chainparams);
    void ProcessMinedBlocks();
    
private:
    void MiningThread(const std::string& address, int threadId);
    bool CheckProofOfWork(const uint256& hash, uint32_t nBits, const Consensus::Params& params);
    void UpdateTime(CBlockHeader* block, const Consensus::Params& consensusParams, const CBlockIndex* pindexPrev);
};

// Global miner instance
extern std::unique_ptr<RXBMiner> g_miner;

void IncrementExtraNonce(CBlock* pblock, const CBlockIndex* pindexPrev, unsigned int& nExtraNonce);
int64_t UpdateTime(CBlockHeader* pblock, const Consensus::Params& consensusParams, const CBlockIndex* pindexPrev);

// RPC commands for RXB mining
UniValue startmining(const JSONRPCRequest& request);
UniValue stopmining(const JSONRPCRequest& request);
UniValue getmininginfo(const JSONRPCRequest& request);
UniValue setgenerate(const JSONRPCRequest& request);

#endif // RXB_MINER_H
