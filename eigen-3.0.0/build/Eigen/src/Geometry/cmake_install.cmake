# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Eigen")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/AlignedBox.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/AngleAxis.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/EulerAngles.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Homogeneous.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Hyperplane.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/OrthoMethods.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/ParametrizedLine.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Quaternion.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Rotation2D.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/RotationBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Scaling.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Transform.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Translation.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry/Umeyama.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Geometry" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/AlignedBox.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/AngleAxis.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/EulerAngles.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Homogeneous.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Hyperplane.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/OrthoMethods.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/ParametrizedLine.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Quaternion.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Rotation2D.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/RotationBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Scaling.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Transform.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Translation.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Geometry/Umeyama.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/Geometry/arch/cmake_install.cmake")

endif()

