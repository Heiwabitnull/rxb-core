// Copyright (c) 2018-2019 The Bitcoin Core developers
// Copyright (c) 2025 The RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>

#include <noui.h>
#include <test/util/logging.h>
#include <test/util/setup_common.h>
#include <util/system.h>
#include <wallet/test/init_test_fixture.h>

BOOST_FIXTURE_TEST_SUITE(init_tests, InitWalletDirTestingSetup)

// ZABEZPIECZENIE PRZED URUCHOMIENIEM TESTOW NA MAINECIE RXB
bool IsRXBMainnetSafe()
{
    return gArgs.GetChainName() == CBaseChainParams::REGTEST;
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_default)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["default"]);
    bool result = m_chain_client->verify();
    BOOST_CHECK(result == true);
    fs::path walletdir = gArgs.GetArg("-walletdir", "");
    fs::path expected_path = fs::canonical(m_walletdir_path_cases["default"]);
    BOOST_CHECK(walletdir == expected_path);
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_custom)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["custom"]);
    bool result = m_chain_client->verify();
    BOOST_CHECK(result == true);
    fs::path walletdir = gArgs.GetArg("-walletdir", "");
    fs::path expected_path = fs::canonical(m_walletdir_path_cases["custom"]);
    BOOST_CHECK(walletdir == expected_path);
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_does_not_exist)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["nonexistent"]);
    {
        ASSERT_DEBUG_LOG("does not exist");
        bool result = m_chain_client->verify();
        BOOST_CHECK(result == false);
    }
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_is_not_directory)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["file"]);
    {
        ASSERT_DEBUG_LOG("is not a directory");
        bool result = m_chain_client->verify();
        BOOST_CHECK(result == false);
    }
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_is_not_relative)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["relative"]);
    {
        ASSERT_DEBUG_LOG("is a relative path");
        bool result = m_chain_client->verify();
        BOOST_CHECK(result == false);
    }
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_no_trailing)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["trailing"]);
    bool result = m_chain_client->verify();
    BOOST_CHECK(result == true);
    fs::path walletdir = gArgs.GetArg("-walletdir", "");
    fs::path expected_path = fs::canonical(m_walletdir_path_cases["default"]);
    BOOST_CHECK(walletdir == expected_path);
}

BOOST_AUTO_TEST_CASE(walletinit_verify_walletdir_no_trailing2)
{
    // BLOKADA NA MAINECIE
    if (!IsRXBMainnetSafe()) {
        BOOST_TEST_MESSAGE("Skipping wallet test on RXB mainnet - safety precaution");
        return;
    }
    
    SetWalletDir(m_walletdir_path_cases["trailing2"]);
    bool result = m_chain_client->verify();
    BOOST_CHECK(result == true);
    fs::path walletdir = gArgs.GetArg("-walletdir", "");
    fs::path expected_path = fs::canonical(m_walletdir_path_cases["default"]);
    BOOST_CHECK(walletdir == expected_path);
}

BOOST_AUTO_TEST_SUITE_END()
