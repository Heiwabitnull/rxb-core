// Copyright (c) 2016-2019 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/bench.h>
#include <bench/data.h>

#include <validation.h>
#include <streams.h>
#include <rpc/blockchain.h>

#include <univalue.h>

static void BlockToJsonVerbose(benchmark::State& state) {
    CDataStream stream(benchmark::data::rxb_genesis_block, SER_NETWORK, PROTOCOL_VERSION);
    char a = '\0';
    stream.write(&a, 1); // Prevent compaction

    CBlock block;
    stream >> block;

    CBlockIndex blockindex;
    const uint256 blockHash = block.GetHash();
    blockindex.phashBlock = &blockHash;
    blockindex.nBits = 0x1e0ffff0; // RXB genesis bits

    while (state.KeepRunning()) {
        (void)blockToJSON(block, &blockindex, &blockindex, /*verbose*/ true);
    }
}

BENCHMARK(BlockToJsonVerbose, 10);
