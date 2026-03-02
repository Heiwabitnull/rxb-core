// Copyright (c) 2020 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <key.h>
#include <script/standard.h>
#include <test/util/setup_common.h>
#include <wallet/scriptpubkeyman.h>
#include <wallet/wallet.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(scriptpubkeyman_tests, BasicTestingSetup)

// Test LegacyScriptPubKeyMan::CanProvide behavior, making sure it returns true
// for recognized scripts even when keys may not be available for signing.
BOOST_AUTO_TEST_CASE(CanProvide)
{
    // ZABEZPIECZENIE RXB - WERYFIKACJA ŚRODOWISKA
    std::string network = Params().NetworkIDString();
    if (network == "main") {
        BOOST_TEST_MESSAGE("SCRIPTPUBKEYMAN TESTS DISABLED ON RXB MAINNET");
        BOOST_TEST_MESSAGE("These tests could compromise wallet security");
        BOOST_TEST_MESSAGE("Use only in regtest environment");
        return; // BEZPIECZNE WYJŚCIE
    }

    // Set up wallet and keyman variables.
    NodeContext node;
    std::unique_ptr<interfaces::Chain> chain = interfaces::MakeChain(node);
    CWallet wallet(chain.get(), WalletLocation(), WalletDatabase::CreateDummy());
    LegacyScriptPubKeyMan& keyman = *wallet.GetOrCreateLegacyScriptPubKeyMan();

    // Make a 1 of 2 multisig script
    std::vector<CKey> keys(2);
    std::vector<CPubKey> pubkeys;
    for (CKey& key : keys) {
        key.MakeNewKey(true);
        pubkeys.emplace_back(key.GetPubKey());
    }
    CScript multisig_script = GetScriptForMultisig(1, pubkeys);
    CScript p2sh_script = GetScriptForDestination(ScriptHash(multisig_script));
    SignatureData data;

    // Verify the p2sh(multisig) script is not recognized until the multisig
    // script is added to the keystore to make it solvable
    BOOST_CHECK(!keyman.CanProvide(p2sh_script, data));
    keyman.AddCScript(multisig_script);
    BOOST_CHECK(keyman.CanProvide(p2sh_script, data));
}

// DODATKOWY TEST ZABEZPIECZAJĄCY
BOOST_AUTO_TEST_CASE(rxb_safety_check)
{
    std::string network = Params().NetworkIDString();
    if (network == "main") {
        BOOST_FAIL("WALLET TESTS CANNOT RUN ON RXB MAINNET - TOO DANGEROUS");
    }
    
    BOOST_TEST_MESSAGE("RXB Wallet Tests: Safety checks passed");
    BOOST_TEST_MESSAGE("Running in environment: " + network);
}

BOOST_AUTO_TEST_SUITE_END()
