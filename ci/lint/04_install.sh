#!/usr/bin/env bash
#
# Copyright (c) 2018-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Adapted for the RXB 2025 system

export LC_ALL=C

# Install code quality tools
travis_retry pip3 install codespell==1.15.0
travis_retry pip3 install flake8==3.7.8
travis_retry pip3 install yq

# Install ShellCheck for linting shell scripts
SHELLCHECK_VERSION=v0.6.0
curl -sL "https://github.com/koalaman/shellcheck/releases/download/${SHELLCHECK_VERSION}/shellcheck-${SHELLCHECK_VERSION}.linux.x86_64.tar.xz" \
  | tar --xz -xf - --directory /tmp/
export PATH="/tmp/shellcheck-${SHELLCHECK_VERSION}:${PATH}"
