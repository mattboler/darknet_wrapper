cmake_minimum_required(VERSION 3.5)
project(darknet_example)

find_package(OpenCV 4.0.0 REQUIRED)
find_package(darknet_wrapper REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${darknet_wrapper_INCLUDE_DIRS})

add_executable(example demo.cpp)
target_link_libraries(example
  ${OpenCV_LIBRARIES}
  ${darknet_wrapper_LIBRARIES}
  )

