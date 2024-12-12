# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/YouTubeApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/YouTubeApp_autogen.dir/ParseCache.txt"
  "YouTubeApp_autogen"
  )
endif()
