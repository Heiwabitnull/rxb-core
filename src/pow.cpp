#include <pow.h>
#include <arith_uint256.h>
#include <chain.h>
#include <consensus/consensus.h>
#include <chainparams.h>
#include <primitives/block.h>
#include <uint256.h>
#include <vector>
#include <algorithm>

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast,
                                 const CBlockHeader* pblock,
                                 const Consensus::Params& params)
{
    assert(pindexLast != nullptr);

    const int64_t N = 60;
    const int64_t T = params.nPowTargetSpacing;
    const int64_t k = N * (N + 1) / 2;

    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);

    if (pindexLast->nHeight < N) {
        return bnPowLimit.GetCompact();
    }

    std::vector<const CBlockIndex*> blocks;
    blocks.reserve(N + 1);

    const CBlockIndex* pindex = pindexLast;
    for (int i = 0; i <= N; ++i) {
        blocks.push_back(pindex);
        pindex = pindex->pprev;
        if (!pindex) {
            return bnPowLimit.GetCompact();
        }
    }

    int64_t weighted_sum = 0;
    for (int i = 0; i < N; ++i) {
        int64_t solvetime = blocks[i]->GetBlockTime() - blocks[i + 1]->GetBlockTime();
        solvetime = std::max<int64_t>(solvetime, 1);
        solvetime = std::min<int64_t>(solvetime, 6 * T);
        int64_t weight    = N - i;
        weighted_sum     += solvetime * weight;
    }

    int64_t LWMA = weighted_sum / k;
    if (LWMA < 1) LWMA = 1;

    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);

    if (T <= 0) {
        return bnPowLimit.GetCompact();
    }

    bnNew *= arith_uint256(LWMA);
    bnNew /= arith_uint256(T);

    arith_uint256 bnPrev;
    bnPrev.SetCompact(pindexLast->nBits);

    arith_uint256 bnMax = bnPrev;
    bnMax /= 3;

    arith_uint256 bnMin = bnPrev;
    bnMin *= 3;

    if (bnNew < bnMax) bnNew = bnMax;
    if (bnNew > bnMin) bnNew = bnMin;

    if (bnNew == 0) {
        bnNew = 1;
    }

    if (bnNew > bnPowLimit) {
        bnNew = bnPowLimit;
    }

    return bnNew.GetCompact();
}

bool CheckProofOfWork(uint256 hash,
                      unsigned int nBits,
                      const Consensus::Params& params)
{
    arith_uint256 bnTarget;
    bnTarget.SetCompact(nBits);

    if (bnTarget <= 0 || bnTarget > UintToArith256(params.powLimit))
        return false;

    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
