cmake_minimum_required(VERSION 3.5)
project(darknet_wrapper)

###############################################################################
## Set compiler options                                                      ##
###############################################################################
# suppress policy warnings on newer versions of cmake
if(NOT(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 3.1))
  #Simplify variable reference and escape sequence evaluation.
  cmake_policy(SET CMP0053 NEW)
endif()

if(NOT(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 3.0))
  # MACOSX_RPATH is enabled by default.
  cmake_policy(SET CMP0042 NEW)
endif()

cmake_policy(SET CMP0057 NEW)


# enable C++11 support
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PKG_BUILD_SYSTEM "standalone" CACHE STRING "Build system to use: {standalone, catkin, ament}")
if(DEFINED ENV{ROS_VERSION})
  if($ENV{ROS_VERSION} EQUAL 1)
    message(STATUS "Build catkin: ROS VERSION: ${ROS_VERSION}")
    set(PKG_BUILD_SYSTEM "catkin")
  elseif($ENV{ROS_VERSION} EQUAL 2)
    message(STATUS "Build ament: ROS VERSION: ${ROS_VERSION}")
    set(PKG_BUILD_SYSTEM "ament")
  else()
    message(ERROR "Failed to parse ROS_VERSION to set build system. ROS VERSION: ${ROS_VERSION}")
  endif()
endif()

###############################################################################
## Find dependencies                                                         ##
###############################################################################

if(NOT DEFINED OpenCV_INCLUDE_DIRS)
  find_package(OpenCV 4.1.0 REQUIRED)
elseif(NOT ${OpenCV_VERSION_MAJOR} STREQUAL "4")
  message(WARNING "OpenCV 4 is required, but opencv${OpenCV_VERSION_MAJOR} has been previously pulled in.. could cause conflicts")
  find_package(OpenCV 4.1.0 REQUIRED)
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

###############################################################################
## Set source files                                                          ##
###############################################################################

set(DARKNET_SRCS
  src/Darknet/Darknet.cpp
)

set(DARKNET_HDRS
  include/Darknet/Darknet.hpp
)


###############################################################################
## Determine CMakeList to build                                              ##
###############################################################################
include(cmake/${PKG_BUILD_SYSTEM}.cmake)
