# CC0 1.0 Universal --- Public Domain
#
# To the extent possible under law, Dante University Foundation and
# Contributors has waived all copyright and related or neighboring
# rights to this file (CMakeLists.txt). This work is published from:
# United States.
#
# Full text of this license can be found in '${KV3_HOME}/licenses/CC-CC0'
# or visit 'https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt' or
# send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
#

target_sources(libkv3 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/cellcopy.c
  ${CMAKE_CURRENT_LIST_DIR}/cellext.c
  ${CMAKE_CURRENT_LIST_DIR}/cellint.c
  ${CMAKE_CURRENT_LIST_DIR}/rowext.c
  ${CMAKE_CURRENT_LIST_DIR}/rowint.c
  ${CMAKE_CURRENT_LIST_DIR}/setext.c
  ${CMAKE_CURRENT_LIST_DIR}/setint.c
  ${CMAKE_CURRENT_LIST_DIR}/strext.c
  ${CMAKE_CURRENT_LIST_DIR}/strint.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefext.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefint.c)
