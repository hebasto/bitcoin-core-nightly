#!/bin/sh
g++-snapshot $FLAGS $STRICT -c txmempool.cpp -o /dev/null > out.txt 2>&1
! grep -q 'error:' out.txt && grep -q 'specified bound 18446744073709551608 exceeds maximum object size' out.txt
