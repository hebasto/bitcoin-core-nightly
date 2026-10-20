# Builds the GCC development snapshot named by GCC_SNAPSHOT (e.g. gcc-17-20261012)
# and installs it into /opt/gcc-snapshot.
#
# The base image matches the one used by libsecp256k1's CI
# (ci/linux-debian.Dockerfile), so that /opt/gcc-snapshot can be copied into
# that image with `COPY --from=` without a glibc mismatch.

FROM debian:stable-slim AS build

ARG GCC_SNAPSHOT
ARG GCC_SNAPSHOT_SHA512

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        ca-certificates wget xz-utils make gcc g++ libc6-dev libgmp-dev libmpfr-dev libmpc-dev flex && \
    mkdir /src && cd /src && \
    wget --progress=dot:giga --https-only "https://gcc.gnu.org/pub/gcc/snapshots/${GCC_SNAPSHOT#gcc-}/${GCC_SNAPSHOT}.tar.xz" && \
    echo "${GCC_SNAPSHOT_SHA512}  ${GCC_SNAPSHOT}.tar.xz" | sha512sum --check && \
    tar xf "${GCC_SNAPSHOT}.tar.xz" && \
    mkdir build && cd build && \
    "../${GCC_SNAPSHOT}/configure" \
        --prefix=/opt/gcc-snapshot \
        --program-suffix=-snapshot \
        --enable-languages=c,c++ \
        --disable-bootstrap \
        --enable-checking=release \
        --disable-multilib \
        --without-isl && \
    make -j "$(nproc)" && \
    make install-strip && \
    echo "${GCC_SNAPSHOT}" > /opt/gcc-snapshot/SNAPSHOT

FROM debian:stable-slim

# Runtime dependencies of the compiler itself and of the programs it produces.
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        binutils libc6-dev libgmp10 libmpfr6 libmpc3 && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

COPY --from=build /opt/gcc-snapshot /opt/gcc-snapshot

# Make the snapshot's libstdc++/libgcc_s the ones found at run time, so that
# programs built with g++-snapshot run inside this image.
#
# ldconfig reads the files in /etc/ld.so.conf.d/ in alphabetical order, and
# the first directory that provides a library wins. The "00-" prefix sorts
# this file before Debian's "<triplet>.conf" on every architecture (without
# it, "aarch64-linux-gnu.conf" is read first and the system libstdc++ is
# picked up on arm64).
RUN ln -s /opt/gcc-snapshot/bin/gcc-snapshot /usr/bin/gcc-snapshot && \
    ln -s /opt/gcc-snapshot/bin/g++-snapshot /usr/bin/g++-snapshot && \
    echo "/opt/gcc-snapshot/lib64" > /etc/ld.so.conf.d/00-gcc-snapshot.conf && \
    echo "/opt/gcc-snapshot/lib" >> /etc/ld.so.conf.d/00-gcc-snapshot.conf && \
    ldconfig
