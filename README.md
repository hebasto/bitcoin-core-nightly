# Nightly Bitcoin Core Tests

This repository performs nightly tests of [Bitcoin Core](https://github.com/bitcoin/bitcoin) across various operating systems and compilers.

For another repository with nightly builds of Bitcoin Core, see [maflcko/b-c-nightly](https://github.com/maflcko/b-c-nightly).

## Modern BSD Derivatives

| Operating System | Status | Build with System Libs | Build with Depends |
|------------------|--------|------------------------|--------------------|
| [FreeBSD](https://www.freebsd.org/) | [![FreeBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/freebsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/freebsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | 1. Release, `MULTIPROCESS=1` |
| [OpenBSD](https://www.openbsd.org/) | [![OpenBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openbsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openbsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | 1. Release, `MULTIPROCESS=1` |
| [NetBSD](https://netbsd.org/) | [![NetBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/netbsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/netbsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | 1. Release, `MULTIPROCESS=1` |

## [illumos](https://illumos.org/)-Based Systems

| Operating System | Status |
|------------------|--------|
| [OmniOS](https://omnios.org/) | [![OmniOS](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/omnios.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/omnios.yml?query=event%3Aschedule) |

## [Clang-SNAPSHOT](https://apt.llvm.org/)

| Operating System | Status |
|------------------|--------|
| Ubuntu 24.04 | [![Clang-SNAPSHOT](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/clang.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/clang.yml?query=event%3Aschedule) |

## [musl](https://musl.libc.org/)-Based Systems

| Operating System | Status |
|------------------|--------|
| [Alpine Linux](https://alpinelinux.org) | [![Alpine](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/alpine.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/alpine.yml?query=event%3Aschedule) |

## Windows

| Operating System | Toolchain | Status | Notes |
|------------------|-----------|--------|-------|
| [Windows 11](https://www.microsoft.com/windows/windows-11) | [Mingw-w64](https://www.mingw-w64.org), MSVCRT | [![Windows](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows.yml?query=event%3Aschedule) | |
| [Windows 11](https://www.microsoft.com/windows/windows-11) | [Mingw-w64](https://www.mingw-w64.org), UCRT | [![Windows, UCRT](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-ucrt.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-ucrt.yml?query=event%3Aschedule) | |
| [Windows 11](https://www.microsoft.com/windows/windows-11) | [MSVC](https://learn.microsoft.com/en-us/cpp/) | [![Windows, MSVC](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-msvc.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-msvc.yml?query=event%3Aschedule) | "Debug" configuration<br>No functional tests |
