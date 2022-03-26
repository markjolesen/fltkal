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

project(kv3)

set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME Runtime)

include(FetchContent)

if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX /usr)
endif()

if (NOT CMAKE_XDGDATA_DIR)
  set(CMAKE_XDGDATA_DIR ${CMAKE_INSTALL_PREFIX}/share)
endif()

FetchContent_Declare(MJO
  GIT_REPOSITORY https://github.com/markjolesen/mjo.git
  GIT_TAG main)

FetchContent_MakeAvailable(MJO)

add_custom_target(install-bin
  DEPENDS kv3
  COMMAND 
  "${CMAKE_COMMAND}"
  -D CMAKE_INSTALL_COMPONENT=Runtime
  -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")

add_custom_target(install-tools
  DEPENDS kv3tocsv csvtokv3
  COMMAND 
  "${CMAKE_COMMAND}"
  -D CMAKE_INSTALL_COMPONENT=Tools
  -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")

add_custom_target(install-all
  DEPENDS install-bin install-tools)

add_subdirectory(lib/kv3)
add_subdirectory(src/app)
add_subdirectory(src/tools)

install(FILES 
  ${CMAKE_CURRENT_LIST_DIR}/database/readme
  ${CMAKE_CURRENT_LIST_DIR}/database/eng.inf
  ${CMAKE_CURRENT_LIST_DIR}/database/eng.ita
  ${CMAKE_CURRENT_LIST_DIR}/database/eng.kv3
  ${CMAKE_CURRENT_LIST_DIR}/database/eng.spa
  ${CMAKE_CURRENT_LIST_DIR}/database/ita.eng
  ${CMAKE_CURRENT_LIST_DIR}/database/ita.inf
  ${CMAKE_CURRENT_LIST_DIR}/database/ita.kv3
  ${CMAKE_CURRENT_LIST_DIR}/database/ita.spa
  ${CMAKE_CURRENT_LIST_DIR}/database/spa.eng
  ${CMAKE_CURRENT_LIST_DIR}/database/spa.inf
  ${CMAKE_CURRENT_LIST_DIR}/database/spa.ita
  ${CMAKE_CURRENT_LIST_DIR}/database/spa.kv3
  DESTINATION "${CMAKE_XDGDATA_DIR}/kv3"
  COMPONENT Runtime)

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/resources/desktop/kv3.desktop
  DESTINATION "${CMAKE_XDGDATA_DIR}/applications"
  COMPONENT Runtime)

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/resources/mime/kv3.xml
  DESTINATION "${CMAKE_XDGDATA_DIR}/mime/packages"
  COMPONENT Runtime)
