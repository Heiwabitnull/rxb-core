// Copyright (c) 2011-2018 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_QT_MACDOCKICONHANDLER_H
#define RXB_QT_MACDOCKICONHANDLER_H

#include <QObject>

/** macOS-specific Dock icon handler for RXB.
 */
class MacDockIconHandler : public QObject
{
    Q_OBJECT

public:
    static MacDockIconHandler *instance();
    static void cleanup();

Q_SIGNALS:
    void dockIconClicked();

private:
    MacDockIconHandler();
};

#endif // RXB_QT_MACDOCKICONHANDLER_H
