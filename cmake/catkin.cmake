message(STATUS "Building with Catkin")
## Find catkin macros and libraries
find_package(catkin REQUIRED)

catkin_package(
  INCLUDE_DIRS include include/Darknet ${CATKIN_DEVEL_PREFIX}
  LIBRARIES ${PROJECT_NAME}
  DEPENDS OpenCV
  CFG_EXTRAS ${PROJECT_NAME}-extras.cmake
)
# CFG_EXTRAS: http://answers.ros.org/question/93266/how-to-export-non-standard-include-directories-in-catkin/

include_directories(include 
  include/Darknet
  ${CATKIN_DEVEL_PREFIX} 
  ${OpenCV_DIRS})

## Declare a cpp library
add_library(${PROJECT_NAME} ${DARKNET_SRCS} ${DARKNET_HDRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

# from timeutils
if(UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} m rt)
endif()


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html
## Mark executables and/or libraries for installation


install(
  TARGETS ${PROJECT_NAME} ${VENOM_EXAMPLES}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


## Mark cpp header files for installation
install(DIRECTORY include/
  DESTINATION include/
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
  PATTERN ".svn" EXCLUDE
)
