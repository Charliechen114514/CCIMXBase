# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/showImage_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/showImage_autogen.dir/ParseCache.txt"
  "showImage_autogen"
  )
endif()
