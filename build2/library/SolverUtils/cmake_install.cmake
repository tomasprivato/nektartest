# Install script for directory: /home/tomas/Documents/gitproject/nektar++/library/SolverUtils

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsolverutilsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/SolverUtils/libSolverUtils-g.so.5.0.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/FieldUtils:/home/tomas/Documents/gitproject/nektar++/build2/library/GlobalMapping:/home/tomas/Documents/gitproject/nektar++/build2/library/MultiRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/Collections:/home/tomas/Documents/gitproject/nektar++/build2/library/LocalRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so.5.0.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xsolverutilsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/SolverUtils/libSolverUtils-g.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/FieldUtils:/home/tomas/Documents/gitproject/nektar++/build2/library/GlobalMapping:/home/tomas/Documents/gitproject/nektar++/build2/library/MultiRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/Collections:/home/tomas/Documents/gitproject/nektar++/build2/library/LocalRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libSolverUtils-g.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Core" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Core/Coupling.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Core" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Core/CouplingFile.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Core" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Core/Misc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Core" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Core/SessionFunction.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/AdvectionSystem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Advection" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Advection/Advection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Advection" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Advection/AdvectionFR.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Advection" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Advection/Advection3DHomogeneous1D.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Advection" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Advection/AdvectionNonConservative.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Advection" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Advection/AdvectionWeakDG.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/Diffusion.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/Diffusion3DHomogeneous1D.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/DiffusionLDG.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/DiffusionLFR.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/DiffusionLFRNS.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Diffusion" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Diffusion/DiffusionIP.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Driver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverAdaptive.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverArnoldi.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverModifiedArnoldi.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverStandard.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverSteadyState.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/EquationSystem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/Filter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterAeroForces.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterAverageFields.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterCheckpoint.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterEnergy1D.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterEnergy.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterError.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterHistoryPoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterModalEnergy.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterMovingAverage.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterFieldConvert.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterThresholdMax.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Filters" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Filters/FilterThresholdMin.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/RiemannSolvers" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/RiemannSolvers/RiemannSolver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/RiemannSolvers" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/RiemannSolvers/UpwindSolver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/RiemannSolvers" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/RiemannSolvers/UpwindLDGSolver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/SolverUtils.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/SolverUtilsDeclspec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/UnsteadySystem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/Forcing.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/ForcingAbsorption.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/ForcingBody.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/ForcingMovingReferenceFrame.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/ForcingNoise.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils/Forcing" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/Forcing/ForcingProgrammatic.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/SolverUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/SolverUtils/DriverArpack.h")
endif()

