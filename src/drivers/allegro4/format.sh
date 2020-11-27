#!/bin/sh
#
# CC0 1.0 Universal --- Public Domain
#
# To the extent possible under law, Mark J. Olesen has waived all copyright
# and related or neighboring rights to this file (kv3_clang_format.sh).
# This work is published from: United States.
#
# Full text of this license can be found by visting
# <https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt> or
# send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
#

find . -type f \( -name '*.c' -o -name '*.h' -o -name '*.cxx' -o -name '*.hxx' \) -exec clang-format -style=file -i {} \;
