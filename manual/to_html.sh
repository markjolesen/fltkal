#!/bin/sh
# ---------------------------------------------------------------------------
# CC0 1.0 Universal --- Public Domain
#
# To the extent possible under law, Dante University Foundation and
# Contributors has waived all copyright and related or neighboring
# rights to this file (to_html.sh). This work is published from:
# United States.
#
# Full text of this license can be found in '${KV3_HOME}/licenses/CC-CC0'
# or visit 'https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt' or
# send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
# ---------------------------------------------------------------------------

# creates kv3 HTML manul using GNU makeinfo

makeinfo --html --no-headers --no-number-sections --no-split kv3.texi
