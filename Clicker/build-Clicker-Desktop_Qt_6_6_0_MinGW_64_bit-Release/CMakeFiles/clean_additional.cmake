# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Clicker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Clicker_autogen.dir\\ParseCache.txt"
  "Clicker_autogen"
  )
endif()
