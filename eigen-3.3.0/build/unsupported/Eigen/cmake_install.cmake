# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Eigen3")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/AdolcForward"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/AlignedVector3"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/ArpackSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/AutoDiff"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/BVH"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/EulerAngles"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/FFT"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/IterativeSolvers"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/KroneckerProduct"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/LevenbergMarquardt"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/MatrixFunctions"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/MoreVectorization"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/MPRealSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/NonLinearOptimization"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/NumericalDiff"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/OpenGLSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/Polynomials"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/Skyline"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/SparseExtra"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/SpecialFunctions"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "E:/MyProject/vs2015TestPrj/eigen-3.3.0/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.3.0/build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

