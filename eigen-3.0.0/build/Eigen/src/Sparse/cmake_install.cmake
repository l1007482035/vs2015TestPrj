# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse

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
   "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/AmbiVector.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/CompressedStorage.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/CoreIterators.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/DynamicSparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/MappedSparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseAssign.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseBlock.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseCwiseBinaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseCwiseUnaryOp.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseDenseProduct.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseDiagonalProduct.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseDot.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseFuzzy.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseMatrixBase.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseProduct.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseRedux.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseSelfAdjointView.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseSparseProduct.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseTranspose.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseTriangularView.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseUtil.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseVector.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/SparseView.h;C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse/TriangularSolver.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen3/Eigen/src/Sparse" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/AmbiVector.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/CompressedStorage.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/CoreIterators.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/DynamicSparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/MappedSparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseAssign.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseBlock.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseCwiseBinaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseCwiseUnaryOp.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseDenseProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseDiagonalProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseDot.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseFuzzy.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseMatrix.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseMatrixBase.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseRedux.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseSelfAdjointView.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseSparseProduct.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseTranspose.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseTriangularView.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseUtil.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseVector.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/SparseView.h"
    "E:/MyProject/vs2015TestPrj/eigen-3.0.0/Eigen/src/Sparse/TriangularSolver.h"
    )
endif()

