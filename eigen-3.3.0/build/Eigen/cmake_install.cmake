# Install script for directory: E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Cholesky"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/CholmodSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Core"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Dense"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Eigen"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Eigenvalues"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Geometry"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Householder"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/IterativeLinearSolvers"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Jacobi"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/LU"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/MetisSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/OrderingMethods"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/PaStiXSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/PardisoSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/QR"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/QtAlignedMalloc"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SPQRSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SVD"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/Sparse"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SparseCholesky"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SparseCore"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SparseLU"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SparseQR"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/StdDeque"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/StdList"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/StdVector"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/SuperLUSupport"
    "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "E:/MyProject/vs2015TestPrj/eigen-3.3.0/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

