// Copyright (c) 2016-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_WALLET_TEST_WALLET_TEST_FIXTURE_H
#define RXB_WALLET_TEST_WALLET_TEST_FIXTURE_H

#include <test/util/setup_common.h>

#include <interfaces/chain.h>
#include <interfaces/wallet.h>
#include <node/context.h>
#include <wallet/wallet.h>

#include <memory>

/** Testing setup and teardown for wallet.
 * 
 *  RXB SECURITY NOTE: Wallet tests are extremely dangerous and should
 *  only be run in isolated regtest environments. Never run wallet tests
 *  on RXB mainnet as they can create real transactions and compromise
 *  wallet security.
 */
struct WalletTestingSetup: public TestingSetup {
    // RXB SAFETY: Changed default from MAIN to REGTEST to prevent
    // accidental execution on mainnet which could damage the live network.
    explicit WalletTestingSetup(const std::string& chainName = CBaseChainParams::REGTEST);

    ~WalletTestingSetup();

    // RXB SECURITY: Add safety check method
    void ValidateTestEnvironment() const;

    NodeContext m_node;
    std::unique_ptr<interfaces::Chain> m_chain = interfaces::MakeChain(m_node);
    std::unique_ptr<interfaces::ChainClient> m_chain_client = interfaces::MakeWalletClient(*m_chain, {});
    CWallet m_wallet;
    std::unique_ptr<interfaces::Handler> m_chain_notifications_handler;
};

#endif // RXB_WALLET_TEST_WALLET_TEST_FIXTURE_H
