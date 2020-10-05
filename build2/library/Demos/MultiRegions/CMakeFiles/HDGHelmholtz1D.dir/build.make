# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tomas/Documents/gitproject/nektar++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tomas/Documents/gitproject/nektar++/build2

# Include any dependencies generated for this target.
include library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/depend.make

# Include the progress variables for this target.
include library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/progress.make

# Include the compile flags for this target's objects.
include library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/flags.make

library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o: library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/flags.make
library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o: ../library/Demos/MultiRegions/HDGHelmholtz1D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o -c /home/tomas/Documents/gitproject/nektar++/library/Demos/MultiRegions/HDGHelmholtz1D.cpp

library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.i"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/Documents/gitproject/nektar++/library/Demos/MultiRegions/HDGHelmholtz1D.cpp > CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.i

library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.s"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/Documents/gitproject/nektar++/library/Demos/MultiRegions/HDGHelmholtz1D.cpp -o CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.s

# Object files for target HDGHelmholtz1D
HDGHelmholtz1D_OBJECTS = \
"CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o"

# External object files for target HDGHelmholtz1D
HDGHelmholtz1D_EXTERNAL_OBJECTS =

library/Demos/MultiRegions/HDGHelmholtz1D: library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/HDGHelmholtz1D.cpp.o
library/Demos/MultiRegions/HDGHelmholtz1D: library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/build.make
library/Demos/MultiRegions/HDGHelmholtz1D: library/MultiRegions/libMultiRegions.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: library/Collections/libCollections.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: library/LocalRegions/libLocalRegions.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: library/SpatialDomains/libSpatialDomains.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: library/StdRegions/libStdRegions.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: library/LibUtilities/libLibUtilities.so.5.0.0
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libboost_thread.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libboost_iostreams.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libboost_program_options.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libboost_filesystem.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libboost_system.so
library/Demos/MultiRegions/HDGHelmholtz1D: /usr/lib/x86_64-linux-gnu/libz.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libtinyxml.a
library/Demos/MultiRegions/HDGHelmholtz1D: /usr/lib/x86_64-linux-gnu/liblapack.so
library/Demos/MultiRegions/HDGHelmholtz1D: /usr/lib/x86_64-linux-gnu/libblas.so
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libscotch.a
library/Demos/MultiRegions/HDGHelmholtz1D: ThirdParty/dist/lib/libscotcherr.a
library/Demos/MultiRegions/HDGHelmholtz1D: library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HDGHelmholtz1D"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HDGHelmholtz1D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/build: library/Demos/MultiRegions/HDGHelmholtz1D

.PHONY : library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/build

library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/clean:
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions && $(CMAKE_COMMAND) -P CMakeFiles/HDGHelmholtz1D.dir/cmake_clean.cmake
.PHONY : library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/clean

library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/depend:
	cd /home/tomas/Documents/gitproject/nektar++/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/Documents/gitproject/nektar++ /home/tomas/Documents/gitproject/nektar++/library/Demos/MultiRegions /home/tomas/Documents/gitproject/nektar++/build2 /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : library/Demos/MultiRegions/CMakeFiles/HDGHelmholtz1D.dir/depend

