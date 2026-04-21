# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support

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
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Block.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Cwise.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/CwiseOperators.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/LU.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Lazy.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/LeastSquares.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Macros.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/MathFunctions.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Memory.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Meta.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/Minor.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/QR.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/SVD.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/TriangularSolver.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support/VectorBlock.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Eigen2Support" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Block.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Cwise.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/CwiseOperators.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/LU.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Lazy.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/LeastSquares.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Macros.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/MathFunctions.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Memory.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Meta.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/Minor.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/QR.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/SVD.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/TriangularSolver.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Eigen2Support/VectorBlock.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/Eigen2Support/Geometry/cmake_install.cmake")

endif()

