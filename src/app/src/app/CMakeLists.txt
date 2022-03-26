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

target_sources(kv3 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/app.cxx
  ${CMAKE_CURRENT_LIST_DIR}/browcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/apfilter.cxx
  ${CMAKE_CURRENT_LIST_DIR}/filtercb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/firstcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/lastcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/nextcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/apopen.cxx
  ${CMAKE_CURRENT_LIST_DIR}/opencb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/prevcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/read.cxx
  ${CMAKE_CURRENT_LIST_DIR}/treecb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/viewcb.cxx
  ${CMAKE_CURRENT_LIST_DIR}/viewchg.cxx)
