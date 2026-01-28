# Nightly Bitcoin Core Tests

This repository performs nightly tests of [Bitcoin Core](https://github.com/bitcoin/bitcoin) across various operating systems and compilers.

For another repository with nightly builds of Bitcoin Core, see [maflcko/b-c-nightly](https://github.com/maflcko/b-c-nightly).

## Modern BSD Derivatives

| Operating System | Releases | Status | Build with System Libs | Build with Depends |
|------------------|:--------:|--------|------------------------|--------------------|
| [FreeBSD](https://www.freebsd.org/) | 15.0 | [![FreeBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/freebsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/freebsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | Release |
| [OpenBSD](https://www.openbsd.org/) | 7.8 | [![OpenBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openbsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openbsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | Release |
| [NetBSD](https://netbsd.org/) | 9.4, 10.1 | [![NetBSD](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/netbsd.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/netbsd.yml?query=event%3Aschedule) | Qt - not installed <br> USDT - N/A | Release |

## [illumos](https://illumos.org/)-Based Systems

| Operating System | Status | Notes |
|------------------|--------|-------|
| [OmniOS](https://omnios.org/) | [![OmniOS](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/omnios.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/omnios.yml?query=event%3Aschedule) | No IPC, no GUI, no ZMQ |
| [OpenIndiana](https://www.openindiana.org/) | [![OpenIndiana](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openindiana.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/openindiana.yml?query=event%3Aschedule) | No IPC, no GUI |

## [Clang-SNAPSHOT](https://apt.llvm.org/)

| Operating System | Status |
|------------------|--------|
| Ubuntu 24.04 | [![Clang-SNAPSHOT](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/clang.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/clang.yml?query=event%3Aworkflow_run) |

## [musl](https://musl.libc.org/)-Based Systems

| Operating System | Status |
|------------------|--------|
| [Alpine Linux](https://alpinelinux.org) | [![Alpine](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/alpine.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/alpine.yml?query=event%3Aschedule) |

## [Windows](https://www.microsoft.com/windows/windows-11)

| Toolchain | Status | Notes |
|-----------|--------|-------|
| [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw), ARM64 | [![Windows, LLVM, arm64](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-llvm-arm64.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-llvm-arm64.yml?query=event%3Aschedule) | |
| [LLVM MinGW](https://github.com/mstorsjo/llvm-mingw), x86_64 | [![Windows, LLVM, x86_64](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-llvm-x86_64.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-llvm-x86_64.yml?query=event%3Aschedule) | |
| GCC, [Mingw-w64](https://www.mingw-w64.org), MSVCRT | [![Windows, GCC, MSVCRT](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-gcc-msvcrt.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-gcc-msvcrt.yml?query=event%3Aworkflow_run) | |
| GCC, [Mingw-w64](https://www.mingw-w64.org), UCRT | [![Windows, GCC, UCRT](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-gcc-ucrt.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-gcc-ucrt.yml?query=event%3Aworkflow_run) | |
| [MSVC](https://learn.microsoft.com/en-us/cpp/) | [![Windows, MSVC](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-msvc.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-msvc.yml?query=event%3Aschedule) | "Debug" configuration<br>No functional tests |
| [clang-cl](https://clang.llvm.org/docs/UsersManual.html#clang-cl) | [![Windows, clang-cl](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-clang-cl.yml/badge.svg)](https://github.com/hebasto/bitcoin-core-nightly/actions/workflows/windows-clang-cl.yml?query=event%3Aworkflow_run) | "Release" configuration<br>No functional tests |
