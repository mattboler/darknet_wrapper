# VENOM Libs

Libraries for **V**isually **E**stimated **N**avigation based on **O**dometry and **M**atching

## Brief

**Venom** libraries include interfaces, structures, and utilites for vision navigation. These utilites are used by ***viper*** (Visual Inertial Position Estimation Routine) visual odometry, and ***cobra*** (Correlation of Optically Built data to Reference Assets) correlation.

___

## Dependancies

- is4s_common v1.1.1
- OpenCV [tested with v4.1.0]: ```brew install opencv```
- yaml-cpp:  ```brew install yaml-cpp```

### Detailed Opencv 4 installation instructions

*Note: prebuilt opencv4 is [available](https://opencv.org/releases/) for osx/ios/android/windows, but must be built from source on linux*

osx installation:

``` bash
brew install opencv
```

linux installation:

``` bash
# Get opencv deps:
sudo apt-get install build-essential # build tools
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev # required
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev # These are optional

mkdir -p $HOME/opencv4
cd $_
git clone -b 4.1.0 https://github.com/opencv/opencv.git
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
            -D CMAKE_INSTALL_PREFIX=/usr/local \
            -D INSTALL_C_EXAMPLES=ON \
            -D INSTALL_PYTHON_EXAMPLES=ON \
            -D WITH_TBB=ON \
            -D WITH_V4L=ON \
            -D OPENCV_PYTHON3_INSTALL_PATH=$cwd/OpenCV-$cvVersion-py3/lib/python3.5/site-packages \
        -D WITH_QT=ON \
        -D WITH_OPENGL=ON \
        -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
        -D ENABLE_PRECOMPILED_HEADERS=OFF \ ## This has to be disabled due to current bug
        -D BUILD_EXAMPLES=ON ..
make -j4
sudo make install

# Optional: build contrib (not used as of now)
cd $HOME/opencv4
git clone -b 4.1.0 https://github.com/opencv/opencv_contrib.git
# build..
```

[installation instructions](https://docs.opencv.org/4.1.0/d7/d9f/tutorial_linux_install.html) from opencv

___

# **Contents**


## **Camera**

Camera modeling utilites for undistortion

___

## **Feature Tracker**

Feature tracking


### **Examples**

#### *visualize_features*

Most concepts of the feature_tracker are represented in this example.  It can grab images from your webcam or a folder of pictures. Use this for feature_tracker development.

Run by calling the visualize features executable with the first arg being a path to the config file

 ```visualize_features /path/to/config.yaml```

Modify the config.yaml with a path to your image source folder, where the image source folder contents are in the following form:

 - 00001.png
 - 00002.png
 - ...
 - nnnnn.png

Or set use_camera to true to use your computers default camera.  Note, did not work at first on osx but worked after running default_camera_test.py.

Note: if using rectified images a camera model still needs to be setup and passed in

___

## **VIPER**

**V**isual **I**nertial **P**osition **E**stimation **R**outine

Contains an implementation of viper, a visual-inertial odometry system.  This implemtation of viper includes a ros node as the transport layer.

>"*A viper has vertically elliptical, or slit-shaped, pupils that can open wide to cover most of the eye or close almost completely, which helps them to see in a wide range of light levels. Typically, vipers are nocturnal and ambush their prey.*"

### *Interfaces*

Interface definition for viper visual odometry framework

### *Structures*

Common visual odometry data structures

### *Utilites*

Common visual odometry tools and utilites

### **Examples**


___

