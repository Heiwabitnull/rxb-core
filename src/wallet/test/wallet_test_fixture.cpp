// Copyright (c) 2016-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <wallet/test/wallet_test_fixture.h>

#include <util/system.h>
#include <chainparams.h>

WalletTestingSetup::WalletTestingSetup(const std::string& chainName)
    : TestingSetup(chainName),
      m_wallet(m_chain.get(), WalletLocation(), WalletDatabase::CreateMock())
{
    // ZABEZPIECZENIE RXB - BLOKADA TESTÓW NA MAINECIE
    std::string network = Params().NetworkIDString();
    if (network == "main") {
        throw std::runtime_error("WALLET TESTS ARE BLOCKED ON RXB MAINNET - TOO DANGEROUS");
    }

    // DODATKOWA WERYFIKACJA DLA BEZPIECZEŃSTWA
    if (gArgs.GetChainName() == CBaseChainParams::MAIN) {
        throw std::runtime_error("Wallet tests cannot run on RXB mainnet for security reasons");
    }

    bool fFirstRun;
    m_wallet.LoadWallet(fFirstRun);
    m_chain_notifications_handler = m_chain->handleNotifications({ &m_wallet, [](CWallet*) {} });
    m_chain_client->registerRpcs();
}

WalletTestingSetup::~WalletTestingSetup()
{
    // Additional cleanup for RXB security
    if (m_wallet.GetBalance() > 0) {
        // Log warning, but do not throw exception in destructor
        LogPrintf("Warning: Test wallet has balance during destruction\n");
    }
}
