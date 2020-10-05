# Install script for directory: /home/tomas/Documents/gitproject/nektar++/docs/user-guide

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  IF (EXISTS /home/tomas/Documents/gitproject/nektar++/build2/docs/user-guide/html)
    FILE(GLOB UGHTML /home/tomas/Documents/gitproject/nektar++/build2/docs/user-guide/html/*)
    LIST(LENGTH UGHTML UGHTML_LEN)
    IF(UGHTML_LEN GREATER 0)
        FILE(INSTALL /home/tomas/Documents/gitproject/nektar++/build2/docs/user-guide/html
             DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/nektar++/user-guide)
    ENDIF()
ENDIF()
IF (EXISTS /home/tomas/Documents/gitproject/nektar++/build2/docs/user-guide/user-guide.pdf)
    FILE(INSTALL /home/tomas/Documents/gitproject/nektar++/build2/docs/user-guide/user-guide.pdf
         DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/nektar++/user-guide)
ENDIF()
endif()

