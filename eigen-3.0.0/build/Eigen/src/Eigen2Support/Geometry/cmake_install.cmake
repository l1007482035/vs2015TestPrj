# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/AlignedBox.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/All.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/AngleAxis.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Hyperplane.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Quaternion.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Rotation2D.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/RotationBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Scaling.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Transform.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry/Translation.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Geometry" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/AlignedBox.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/All.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/AngleAxis.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Hyperplane.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Quaternion.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Rotation2D.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/RotationBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Scaling.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Transform.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Geometry/Translation.h"
    )
endif()

