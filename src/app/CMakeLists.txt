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

set(FLTK_SKIP_FLUID TRUE)
set(FLTK_SKIP_FORMS TRUE)
set(FLTK_SKIP_IMAGES TRUE)
set(FLTK_SKIP_OPENGL TRUE)

find_package(FLTK REQUIRED
  HINTS
  ${FLTK_DIR}
  ${CMAKE_INSTALL_PREFIX}/share/fltk)

if (NOT FLTK_LIBRARIES)
  set(FLTK_LIBRARIES fltk)
endif()

add_executable(kv3)

target_include_directories(kv3 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/../icon/xpm
  $<TARGET_PROPERTY:libmjo,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:libmjoextra,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:libkv3,INTERFACE_INCLUDE_DIRECTORIES>
  ${FLTK_INCLUDE_DIRS})

add_subdirectory(src)

target_link_libraries(kv3 LINK_PRIVATE
  libkv3
  libmjoextra
  libmjo
  ${FLTK_LIBRARIES})

install(TARGETS kv3
  RUNTIME DESTINATION bin
  COMPONENT Runtime)

install(FILES
  kv3.1
  DESTINATION man/man1
  COMPONENT Runtime)
