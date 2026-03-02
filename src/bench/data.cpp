// Copyright (c) 2019 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/data.h>
#include <util/strencodings.h>

namespace benchmark {
namespace data {

// RXB Genesis Block data
const std::vector<uint8_t> rxb_genesis_block = ParseHex(
    "010000000000000000000000000000000000000000000000000000000000000000000000942f1c3e9ec307bbd002296886426d44059e1f7dcb71a60969277938b7d50731ae3c0369f0ff0f1ebd7e18000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff4cf0ff0f1e01000000435468652047617a612063656173656669726520697320616e20696d706f7274616e74206669727374207374657020746f7761726473206c617374696e67207065616365ffffffff0100e40b5402000000126a10426974636f696e582047656e6573697300000000"
);

} // namespace data
} // namespace benchmark
