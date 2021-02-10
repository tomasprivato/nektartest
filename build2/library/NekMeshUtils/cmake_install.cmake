# Install script for directory: /home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xnekmeshutilsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/NekMeshUtils/libNekMeshUtils-g.so.5.0.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so.5.0.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xnekmeshutilsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/NekMeshUtils/libNekMeshUtils-g.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libNekMeshUtils-g.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/NekMeshUtilsDeclspec.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/Module" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/Module/Module.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Node.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Edge.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Face.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Element.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Composite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Mesh.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Point.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Line.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Triangle.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Quadrilateral.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Tetrahedron.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Pyramid.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Prism.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/Hexahedron.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/HOAlignment.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/MeshElements" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/MeshElements/ElementConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/CADObject.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/CADSystem.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/CADVert.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/CADCurve.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/CADSurf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils/CADSystem" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/CADSystem/ProcessLoadCAD.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/NekMeshUtils" TYPE DIRECTORY FILES "/home/tomas/Documents/gitproject/nektar++/library/NekMeshUtils/./" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

