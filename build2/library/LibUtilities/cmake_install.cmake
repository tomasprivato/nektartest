# Install script for directory: /home/tomas/Documents/gitproject/nektar++/library/LibUtilities

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibutilitiesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities/libLibUtilities-g.so.5.0.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so.5.0.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibutilitiesx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities/libLibUtilities-g.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libLibUtilities-g.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Memory" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Memory/ThreadSpecificPool.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Memory" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Memory/NekMemoryManager.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ArrayPolicies.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/CheckedCast.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ConsistentObjectAccess.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/CompressData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/CsvIO.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Equation.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/FieldIO.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/FieldIOXml.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/FileSystem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ErrorUtil.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Interpolator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/HashUtils.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/NekManager.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/NekFactory.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ParseUtils.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Progressbar.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/PtsField.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/PtsIO.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Timer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/RawType.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/RealComparison.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/SessionReader.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ShapeType.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/SharedArray.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Thread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/ThreadBoost.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Vmath.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/VmathArray.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/Metis.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicUtils/VtkUtil.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Polylib" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Polylib/Polylib.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/Comm.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/CommSerial.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/CommDataType.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/GsLib.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/Transposition.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Communication" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Communication/Xxt.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/Basis.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/BasisType.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/BLPoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/FoundationsFwd.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/Foundations.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/FourierPoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/FourierSingleModePoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/GaussPoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/Graph.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/InterpCoeff.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/Interp.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/ManagerAccess.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalPrismEvenlySpaced.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalPrismElec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTetElecData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTetElec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTetEvenlySpaced.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriElecData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriElec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriEvenlySpaced.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriFeketeData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriFekete.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriSPIData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTriSPI.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTetSPI.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalPrismSPI.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalTetSPIData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalQuadElec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalHexElec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/NodalUtil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/PhysGalerkinProject.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/Points.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/PointsType.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Foundations" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Foundations/PolyEPoints.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/Arpack.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/BlasArray.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/Blas.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/BlockMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/CanGetRawPtr.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/ExplicitInstantiation.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/Lapack.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/MatrixBase.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/MatrixFuncs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/MatrixOperations.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/MatrixStorageType.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/MatrixType.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekLinAlgAlgorithms.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekLinSys.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekMatrixFwd.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekPoint.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekTypeDefs.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekVectorFwd.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NekVector.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/PointerWrapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/ScaledMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/StandardMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/TransF77.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/StorageSmvBsr.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/NistSparseDescriptors.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/SparseDiagBlkMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/SparseMatrix.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/SparseMatrixFwd.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./LinearAlgebra" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./LinearAlgebra/SparseUtils.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicConst" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicConst/NektarUnivConsts.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicConst" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicConst/NektarUnivTypeDefs.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./BasicConst" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./BasicConst/GitRevision.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Interpreter" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Interpreter/Interpreter.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./Kernel" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./Kernel/kernel.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/AdamsBashforthTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/AdamsMoultonTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/BDFImplicitTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/EulerTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/CNABTimeIntegrationScheme.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/DIRKTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/IMEXGearTimeIntegrationScheme.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/IMEXTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/IMEXdirkTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/MCNABTimeIntegrationScheme.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/RungeKuttaTimeIntegrationSchemes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/TimeIntegrationScheme.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/TimeIntegrationSchemeData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./TimeIntegration" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./TimeIntegration/TimeIntegrationSolution.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities/./FFT" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./FFT/NektarFFT.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/LibUtilitiesDeclspec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/LibUtilities" TYPE DIRECTORY FILES "/home/tomas/Documents/gitproject/nektar++/library/LibUtilities/./" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

