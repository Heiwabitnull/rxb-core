// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparamsbase.h>

#include <tinyformat.h>
#include <util/system.h>
#include <util/memory.h>

#include <assert.h>

// Only supported chain
const std::string CBaseChainParams::MAIN = "main";

/**
 * Adds -chain option to program arguments.
 * Only main chain is supported
 */
void SetupChainParamsBaseOptions()
{
    gArgs.AddArg("-chain=<chain>", 
                 "Use the chain <chain> (default: main). Allowed values: main", 
                 ArgsManager::ALLOW_ANY, 
                 OptionsCategory::CHAINPARAMS);
}

// Global pointer to base chain parameters
static std::unique_ptr<CBaseChainParams> globalChainBaseParams;

/**
 * Returns currently selected base parameters
 */
const CBaseChainParams& BaseParams()
{
    assert(globalChainBaseParams);
    return *globalChainBaseParams;
}

/**
 * Creates base parameters object for specified chain
 * Note: testnet/regtest removed
 * RPC port set to 8328 (P2P = 8327 + 1)
 */
std::unique_ptr<CBaseChainParams> CreateBaseChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return MakeUnique<CBaseChainParams>("", 8328);
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

/**
 * Sets global base parameters pointer
 */
void SelectBaseParams(const std::string& chain)
{
    globalChainBaseParams = CreateBaseChainParams(chain);
    gArgs.SelectConfigNetwork(chain);
}
