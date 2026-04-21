# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen

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
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Array;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Cholesky;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Core;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Dense;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Eigen;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Eigen2Support;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Eigenvalues;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Geometry;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Householder;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Jacobi;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/LU;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/LeastSquares;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/QR;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/QtAlignedMalloc;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/SVD;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/Sparse;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/StdDeque;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/StdList;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/StdVector")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Array"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Cholesky"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Core"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Dense"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Eigen"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Eigen2Support"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Eigenvalues"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Geometry"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Householder"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Jacobi"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/LU"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/LeastSquares"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/QR"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/QtAlignedMalloc"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/SVD"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/Sparse"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/StdDeque"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/StdList"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/StdVector"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/cmake_install.cmake")

endif()

