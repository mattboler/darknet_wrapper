message(STATUS "Building with Ament")
find_package(ament_cmake_auto REQUIRED)

# find dependencies
ament_auto_find_build_dependencies()

include_directories(include
  inculde/Darknet)

# setup targets
ament_auto_add_library(${PROJECT_NAME} ${DARKNET_SRCS} ${DARKNET_HDRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

# When other packages include this project, they will get access to these:
ament_export_include_directories(include include/modules
                                ${OpenCV_INCLUDE_DIRS})
                                 
ament_export_libraries(${PROJECT_NAME})

option(BUILD_VENOM_EXAMPLES "Build examples." ON)
set(VENOM_EXAMPLES "")
if(BUILD_VENOM_EXAMPLES)
add_executable(visualize_camera_model examples/modules/camera_model/visualize_camera_model.cpp)
target_link_libraries(visualize_camera_model ${PROJECT_NAME} ${YAML_CPP_LIBRARIES})

add_executable(visualize_features examples/modules/feature_tracker/visualize_features.cpp)
target_link_libraries(visualize_features ${PROJECT_NAME} ${YAML_CPP_LIBRARIES})

set(VENOM_EXAMPLES 
  visualize_camera_model
  visualize_features
)
endif(BUILD_VENOM_EXAMPLES)

message(STATUS "Examples: ${VENOM_EXAMPLES}")


##############
## RosNodes ##
##############
option(BUILD_ROS_NODE "Build examples." OFF)
set(ROS_NODE_EXECUTABLE "")
if(BUILD_ROS_NODE)
  find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    sensor_msgs
    std_srvs
    cv_bridge
    tf2_ros
    ${PROJECT_NAME})

  include_directories(include 
    include/modules
    include/modules/viper/transport
    include/modules/feature_tracker/transport
    ${CATKIN_DEVEL_PREFIX} 
    ${catkin_INCLUDE_DIRS}
    ${is4s_common_DIRS}
    ${OpenCV_DIRS}
    ${venom_INCLUDE_DIRS})

  add_executable(feature_tracker_node src/modules/feature_tracker/transport/feature_tracker_node.cpp)
  target_link_libraries(feature_tracker_node ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})

  add_executable(viper_node src/modules/viper/transport/viper_node.cpp)
  target_link_libraries(viper_node ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})

  set(ROS_NODE_EXECUTABLE 
    feature_tracker_node
    viper_node
  )
endif(BUILD_ROS_NODE)

###############################################################################
## Install                                                                   ##
###############################################################################

install(
  TARGETS ${PROJECT_NAME} ${VENOM_EXAMPLES} ${ROS_NODE_EXECUTABLE}
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

install(DIRECTORY launch/launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  )

install(DIRECTORY launch/config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
  )


# export information to downstream packages
ament_auto_package()
