// Copyright (c) 2018-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_WALLET_TEST_INIT_TEST_FIXTURE_H
#define RXB_WALLET_TEST_INIT_TEST_FIXTURE_H

#include <interfaces/chain.h>
#include <node/context.h>
#include <test/util/setup_common.h>
#include <util/system.h>

#include <stdexcept>
#include <string>

struct InitWalletDirTestingSetup: public BasicTestingSetup {
    explicit InitWalletDirTestingSetup(const std::string& chainName = CBaseChainParams::REGTEST);
    ~InitWalletDirTestingSetup();
    void SetWalletDir(const fs::path& walletdir_path);

    // Security function - block tests on RXB mainnet
    void CheckMainnetSafety(const std::string& chainName)
    {
        if (chainName == CBaseChainParams::MAIN) {
            throw std::runtime_error(
                "WALLET TESTS ARE BLOCKED ON RXB MAINNET FOR SAFETY\n"
                "Running wallet tests on mainnet could:\n"
                "- Create real transactions and waste BX\n"
                "- Damage the live blockchain\n"
                "- Compromise private keys\n"
                "Use only with -regtest or -testnet (if available)"
            );
        }
        
        // Additional check via environment variables
        if (gArgs.GetChainName() == CBaseChainParams::MAIN) {
            throw std::runtime_error("RXB wallet tests cannot run on mainnet - check your configuration");
        }
    }

    fs::path m_datadir;
    fs::path m_cwd;
    std::map<std::string, fs::path> m_walletdir_path_cases;
    NodeContext m_node;
    std::unique_ptr<interfaces::Chain> m_chain = interfaces::MakeChain(m_node);
    std::unique_ptr<interfaces::ChainClient> m_chain_client;
};

#endif // RXB_WALLET_TEST_INIT_TEST_FIXTURE_H
