# Install script for directory: /home/tomas/Documents/gitproject/nektar++/utilities/FieldConvert

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xfieldconvertx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g"
         RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE OPTIONAL FILES "/home/tomas/Documents/gitproject/nektar++/build2/utilities/FieldConvert/FieldConvert-g")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g"
         OLD_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib:/home/tomas/Documents/gitproject/nektar++/build2/library/FieldUtils:/home/tomas/Documents/gitproject/nektar++/build2/library/GlobalMapping:/home/tomas/Documents/gitproject/nektar++/build2/library/MultiRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/Collections:/home/tomas/Documents/gitproject/nektar++/build2/library/LocalRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/SpatialDomains:/home/tomas/Documents/gitproject/nektar++/build2/library/StdRegions:/home/tomas/Documents/gitproject/nektar++/build2/library/LibUtilities:"
         NEW_RPATH "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64:/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty/")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FieldConvert-g")
    endif()
  endif()
endif()

