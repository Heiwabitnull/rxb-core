// Copyright (c) 2018 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_COMPAT_STDIN_H
#define RXB_COMPAT_STDIN_H

struct NoechoInst {
    NoechoInst();
    ~NoechoInst();
};

#define NO_STDIN_ECHO() NoechoInst _no_echo

bool StdinTerminal();
bool StdinReady();

#endif // RXB_COMPAT_STDIN_H
