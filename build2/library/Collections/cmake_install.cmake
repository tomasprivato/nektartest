# Install script for directory: /home/tomas/Documents/gitproject/nektar++/library/Collections

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcollectionsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/Collections/libCollections-g.so.5.0.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/LocalRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so.5.0.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcollectionsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/library/Collections/libCollections-g.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/LocalRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libCollections-g.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/CoalescedGeomData.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/Collection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/CollectionOptimisation.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/IProduct.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE FILE FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/Operator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/nektar++/Collections" TYPE DIRECTORY FILES "/home/tomas/Documents/gitproject/nektar++/library/Collections/./" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

