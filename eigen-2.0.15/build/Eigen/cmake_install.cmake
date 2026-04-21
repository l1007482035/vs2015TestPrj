# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen

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
   "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Core;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/LU;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Cholesky;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/QR;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Geometry;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Sparse;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Array;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/SVD;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/LeastSquares;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/QtAlignedMalloc;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/StdVector;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/NewStdVector;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Eigen;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Dense")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen2/Eigen" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Core"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/LU"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Cholesky"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/QR"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Geometry"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Sparse"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Array"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/SVD"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/LeastSquares"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/QtAlignedMalloc"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/StdVector"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/NewStdVector"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Eigen"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/Dense"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-2.0.15/build/Eigen/src/cmake_install.cmake")

endif()

