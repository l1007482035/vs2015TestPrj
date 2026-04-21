# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
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
   "/Eigen/src/Core/Assign.h;/Eigen/src/Core/Block.h;/Eigen/src/Core/CacheFriendlyProduct.h;/Eigen/src/Core/Coeffs.h;/Eigen/src/Core/CommaInitializer.h;/Eigen/src/Core/Cwise.h;/Eigen/src/Core/CwiseBinaryOp.h;/Eigen/src/Core/CwiseNullaryOp.h;/Eigen/src/Core/CwiseUnaryOp.h;/Eigen/src/Core/DiagonalCoeffs.h;/Eigen/src/Core/DiagonalMatrix.h;/Eigen/src/Core/DiagonalProduct.h;/Eigen/src/Core/Dot.h;/Eigen/src/Core/Flagged.h;/Eigen/src/Core/Functors.h;/Eigen/src/Core/Fuzzy.h;/Eigen/src/Core/GenericPacketMath.h;/Eigen/src/Core/IO.h;/Eigen/src/Core/Map.h;/Eigen/src/Core/MapBase.h;/Eigen/src/Core/MathFunctions.h;/Eigen/src/Core/Matrix.h;/Eigen/src/Core/MatrixBase.h;/Eigen/src/Core/MatrixStorage.h;/Eigen/src/Core/Minor.h;/Eigen/src/Core/NestByValue.h;/Eigen/src/Core/NumTraits.h;/Eigen/src/Core/Part.h;/Eigen/src/Core/Product.h;/Eigen/src/Core/Redux.h;/Eigen/src/Core/SolveTriangular.h;/Eigen/src/Core/Sum.h;/Eigen/src/Core/Swap.h;/Eigen/src/Core/Transpose.h;/Eigen/src/Core/Visitor.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Eigen/src/Core" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Assign.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Block.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/CacheFriendlyProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Coeffs.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/CommaInitializer.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Cwise.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/CwiseBinaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/CwiseNullaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/CwiseUnaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/DiagonalCoeffs.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/DiagonalMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/DiagonalProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Dot.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Flagged.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Functors.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Fuzzy.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/GenericPacketMath.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/IO.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Map.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/MapBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/MathFunctions.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Matrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/MatrixBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/MatrixStorage.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Minor.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/NestByValue.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/NumTraits.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Part.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Product.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Redux.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/SolveTriangular.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Sum.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Swap.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Transpose.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Core/Visitor.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/build/Core/util/cmake_install.cmake")
  include("E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/build/Core/arch/cmake_install.cmake")

endif()

