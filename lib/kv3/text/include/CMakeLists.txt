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

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/text.h
  ${CMAKE_CURRENT_LIST_DIR}/textcell.h
  ${CMAKE_CURRENT_LIST_DIR}/textlink.h
  ${CMAKE_CURRENT_LIST_DIR}/textseg.h
  ${CMAKE_CURRENT_LIST_DIR}/textset.h
  ${CMAKE_CURRENT_LIST_DIR}/textsubj.h
  DESTINATION include/kv3
  COMPONENT Development
  EXCLUDE_FROM_ALL)
