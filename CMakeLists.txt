cmake_minimum_required(VERSION 2.8)
project(BeatCounter)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_subdirectory(Builds/MacOSX)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_subdirectory(Builds/Linux)
endif()
