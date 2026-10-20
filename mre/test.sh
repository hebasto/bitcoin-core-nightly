#!/bin/sh
! grep -q '^# *[0-9]' txmempool.ii || exit 1
g++-snapshot $FLAGS $STRICT -c txmempool.ii -o /dev/null > out.txt 2>&1
! grep -q 'error:' out.txt && grep -q 'specified bound 18446744073709551608 exceeds maximum object size' out.txt
