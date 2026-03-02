// Copyright (c) 2019 The Bitcoin Core developers
// Copyright (c) 2025 RXB developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_NET_TYPES_H
#define RXB_NET_TYPES_H

#include <map>

class CBanEntry;
class CSubNet;

using banmap_t = std::map<CSubNet, CBanEntry>;

#endif // RXB_NET_TYPES_H
