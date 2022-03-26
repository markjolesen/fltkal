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

project(csvtokv3)

add_executable(csvtokv3 
	version.c
	main.c)

target_link_libraries(csvtokv3 LINK_PRIVATE
  libkv3
  libmjoextra
  libmjo)

target_include_directories(csvtokv3 PRIVATE
  $<TARGET_PROPERTY:libkv3,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:libmjoextra,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:libmjo,INTERFACE_INCLUDE_DIRECTORIES>)

install(TARGETS csvtokv3
  RUNTIME DESTINATION bin
  COMPONENT Tools
  EXCLUDE_FROM_ALL)

install(FILES
	csvtokv3.1
	DESTINATION man/man1
	COMPONENT Tools
	EXCLUDE_FROM_ALL)
