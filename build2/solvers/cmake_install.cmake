# Install script for directory: /home/tomas/Documents/gitproject/nektar++/solvers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tomas/Documents/gitproject/nektar++/build2/dist")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/ADRSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/AcousticSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/CardiacEPSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/CompressibleFlowSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/DummySolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/ImageWarpingSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/LinearElasticSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/MMFSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/PulseWaveSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/ShallowWaterSolver/cmake_install.cmake")
  include("/home/tomas/Documents/gitproject/nektar++/build2/solvers/VortexWaveInteraction/cmake_install.cmake")

endif()

