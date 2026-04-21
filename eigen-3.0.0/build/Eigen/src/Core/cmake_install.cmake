# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core

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
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Array.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/ArrayBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/ArrayWrapper.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Assign.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/BandMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Block.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/BooleanRedux.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/CommaInitializer.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/CwiseBinaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/CwiseNullaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/CwiseUnaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/CwiseUnaryView.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/DenseBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/DenseCoeffsBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/DenseStorage.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Diagonal.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/DiagonalMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/DiagonalProduct.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Dot.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/EigenBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Flagged.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/ForceAlignedAccess.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Functors.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Fuzzy.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/GenericPacketMath.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/GlobalFunctions.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/IO.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Map.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/MapBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/MathFunctions.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Matrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/MatrixBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/NestByValue.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/NoAlias.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/NumTraits.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/PermutationMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/PlainObjectBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Product.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/ProductBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Random.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Redux.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Replicate.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/ReturnByValue.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Reverse.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Select.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/SelfAdjointView.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/SelfCwiseBinaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/SolveTriangular.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/StableNorm.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Stride.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Swap.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Transpose.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Transpositions.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/TriangularMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/VectorBlock.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/VectorwiseOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core/Visitor.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Core" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Array.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/ArrayBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/ArrayWrapper.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Assign.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/BandMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Block.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/BooleanRedux.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/CommaInitializer.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/CwiseBinaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/CwiseNullaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/CwiseUnaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/CwiseUnaryView.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/DenseBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/DenseCoeffsBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/DenseStorage.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Diagonal.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/DiagonalMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/DiagonalProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Dot.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/EigenBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Flagged.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/ForceAlignedAccess.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Functors.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Fuzzy.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/GenericPacketMath.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/GlobalFunctions.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/IO.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Map.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/MapBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/MathFunctions.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Matrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/MatrixBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/NestByValue.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/NoAlias.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/NumTraits.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/PermutationMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/PlainObjectBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Product.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/ProductBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Random.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Redux.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Replicate.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/ReturnByValue.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Reverse.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Select.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/SelfAdjointView.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/SelfCwiseBinaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/SolveTriangular.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/StableNorm.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Stride.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Swap.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Transpose.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Transpositions.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/TriangularMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/VectorBlock.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/VectorwiseOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Core/Visitor.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/Core/products/cmake_install.cmake")
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/Core/util/cmake_install.cmake")
  include("E:/MyProject/vs2015TestPrj/eigen-3.0.0/build/Eigen/src/Core/arch/cmake_install.cmake")

endif()

