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

cmake_minimum_required (VERSION 3.20.3)

project(libkv3)

if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX /usr)
endif()

add_library(libkv3 STATIC)

set_target_properties(libkv3 PROPERTIES OUTPUT_NAME kv3)

target_include_directories(libkv3
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/dict/include
    ${CMAKE_CURRENT_LIST_DIR}/text/include
    ${CMAKE_CURRENT_LIST_DIR}/db/include
    $<TARGET_PROPERTY:libmjo,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:libmjoextra,INTERFACE_INCLUDE_DIRECTORIES>)

add_subdirectory(dict)
add_subdirectory(text)
add_subdirectory(db)

install(TARGETS libkv3
  DESTINATION lib
  COMPONENT Development
  EXCLUDE_FROM_ALL)
