// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2025 RXB Hard Fork developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RXB_QT_RXBADDRESSVALIDATOR_H
#define RXB_QT_RXBADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class RXBAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit RXBAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** RXB address widget validator, checks for a valid rxb address.
 */
class RXBAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit RXBAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // RXB_QT_RXBADDRESSVALIDATOR_H
