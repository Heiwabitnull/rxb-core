// Copyright (c) 2011-2019 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_QT_COINCONTROLTREEWIDGET_H
#define RXB_QT_COINCONTROLTREEWIDGET_H

#include <QKeyEvent>
#include <QTreeWidget>

class CoinControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget *parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // RXB_QT_COINCONTROLTREEWIDGET_H
