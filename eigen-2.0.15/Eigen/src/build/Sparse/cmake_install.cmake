# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Eigen/src/Sparse/AmbiVector.h;/Eigen/src/Sparse/CholmodSupport.h;/Eigen/src/Sparse/CompressedStorage.h;/Eigen/src/Sparse/CoreIterators.h;/Eigen/src/Sparse/DynamicSparseMatrix.h;/Eigen/src/Sparse/MappedSparseMatrix.h;/Eigen/src/Sparse/RandomSetter.h;/Eigen/src/Sparse/SparseAssign.h;/Eigen/src/Sparse/SparseBlock.h;/Eigen/src/Sparse/SparseCwise.h;/Eigen/src/Sparse/SparseCwiseBinaryOp.h;/Eigen/src/Sparse/SparseCwiseUnaryOp.h;/Eigen/src/Sparse/SparseDiagonalProduct.h;/Eigen/src/Sparse/SparseDot.h;/Eigen/src/Sparse/SparseFlagged.h;/Eigen/src/Sparse/SparseFuzzy.h;/Eigen/src/Sparse/SparseLDLT.h;/Eigen/src/Sparse/SparseLLT.h;/Eigen/src/Sparse/SparseLU.h;/Eigen/src/Sparse/SparseMatrix.h;/Eigen/src/Sparse/SparseMatrixBase.h;/Eigen/src/Sparse/SparseProduct.h;/Eigen/src/Sparse/SparseRedux.h;/Eigen/src/Sparse/SparseTranspose.h;/Eigen/src/Sparse/SparseUtil.h;/Eigen/src/Sparse/SparseVector.h;/Eigen/src/Sparse/SuperLUSupport.h;/Eigen/src/Sparse/TaucsSupport.h;/Eigen/src/Sparse/TriangularSolver.h;/Eigen/src/Sparse/UmfPackSupport.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Eigen/src/Sparse" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/AmbiVector.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/CholmodSupport.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/CompressedStorage.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/CoreIterators.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/DynamicSparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/MappedSparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/RandomSetter.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseAssign.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseBlock.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseCwise.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseCwiseBinaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseCwiseUnaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseDiagonalProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseDot.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseFlagged.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseFuzzy.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseLDLT.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseLLT.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseLU.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseMatrixBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseRedux.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseTranspose.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseUtil.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SparseVector.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/SuperLUSupport.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/TaucsSupport.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/TriangularSolver.h"
    "E:/MyProject/vs2015TestPrj/eigen-2.0.15/Eigen/src/Sparse/UmfPackSupport.h"
    )
endif()

