# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen

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
   "C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/AdolcForward;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/BVH;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/IterativeSolvers;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/MatrixFunctions;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/MoreVectorization;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/AutoDiff;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/AlignedVector3;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/Polynomials;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/CholmodSupport;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/FFT;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/NonLinearOptimization;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/SparseExtra;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/SuperLUSupport;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/UmfPackSupport;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/IterativeSolvers;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/NumericalDiff;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/Skyline;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/MPRealSupport;C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen/OpenGLSupport")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/AdolcForward"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/BVH"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/IterativeSolvers"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/MatrixFunctions"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/MoreVectorization"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/AutoDiff"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/AlignedVector3"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/Polynomials"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/CholmodSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/FFT"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/NonLinearOptimization"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/SparseExtra"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/SuperLUSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/UmfPackSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/IterativeSolvers"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/NumericalDiff"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/Skyline"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/MPRealSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/unsupported/Eigen/OpenGLSupport"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/unsupported/Eigen/src/cmake_install.cmake")

endif()

