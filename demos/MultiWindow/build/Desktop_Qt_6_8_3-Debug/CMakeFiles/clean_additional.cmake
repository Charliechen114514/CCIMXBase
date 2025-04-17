# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MultiWindow_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MultiWindow_autogen.dir/ParseCache.txt"
  "MultiWindow_autogen"
  )
endif()
