# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/demo_more_buttons_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/demo_more_buttons_autogen.dir/ParseCache.txt"
  "demo_more_buttons_autogen"
  )
endif()
