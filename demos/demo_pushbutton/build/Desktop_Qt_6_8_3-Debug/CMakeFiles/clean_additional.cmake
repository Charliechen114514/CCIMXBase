# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/demo_pushbutton_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/demo_pushbutton_autogen.dir/ParseCache.txt"
  "demo_pushbutton_autogen"
  )
endif()
