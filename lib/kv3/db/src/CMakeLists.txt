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
  ${CMAKE_CURRENT_LIST_DIR}/datumass.c
  ${CMAKE_CURRENT_LIST_DIR}/datumdis.c
  ${CMAKE_CURRENT_LIST_DIR}/datumopn.c
  ${CMAKE_CURRENT_LIST_DIR}/datumrd.c
  ${CMAKE_CURRENT_LIST_DIR}/infass.c
  ${CMAKE_CURRENT_LIST_DIR}/infdis.c
  ${CMAKE_CURRENT_LIST_DIR}/infload.c
  ${CMAKE_CURRENT_LIST_DIR}/tableass.c
  ${CMAKE_CURRENT_LIST_DIR}/tabledis.c
  ${CMAKE_CURRENT_LIST_DIR}/tableopn.c
  ${CMAKE_CURRENT_LIST_DIR}/tablerd.c
  ${CMAKE_CURRENT_LIST_DIR}/troveass.c
  ${CMAKE_CURRENT_LIST_DIR}/trovedis.c
  ${CMAKE_CURRENT_LIST_DIR}/troveopn.c
  ${CMAKE_CURRENT_LIST_DIR}/troverd.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefass.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefdis.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefopn.c
  ${CMAKE_CURRENT_LIST_DIR}/xrefrd.c)
