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
include library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/depend.make

# Include the progress variables for this target.
include library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/progress.make

# Include the compile flags for this target's objects.
include library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/flags.make

library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o: library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/flags.make
library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o: ../library/Demos/SpatialDomains/PartitionAnalyse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o -c /home/tomas/Documents/gitproject/nektar++/library/Demos/SpatialDomains/PartitionAnalyse.cpp

library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.i"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/Documents/gitproject/nektar++/library/Demos/SpatialDomains/PartitionAnalyse.cpp > CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.i

library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.s"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/Documents/gitproject/nektar++/library/Demos/SpatialDomains/PartitionAnalyse.cpp -o CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.s

# Object files for target PartitionAnalyse
PartitionAnalyse_OBJECTS = \
"CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o"

# External object files for target PartitionAnalyse
PartitionAnalyse_EXTERNAL_OBJECTS =

library/Demos/SpatialDomains/PartitionAnalyse: library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/PartitionAnalyse.cpp.o
library/Demos/SpatialDomains/PartitionAnalyse: library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/build.make
library/Demos/SpatialDomains/PartitionAnalyse: library/SpatialDomains/libSpatialDomains.so.5.0.0
library/Demos/SpatialDomains/PartitionAnalyse: library/StdRegions/libStdRegions.so.5.0.0
library/Demos/SpatialDomains/PartitionAnalyse: library/LibUtilities/libLibUtilities.so.5.0.0
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libboost_thread.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libboost_iostreams.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libboost_program_options.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libboost_filesystem.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libboost_system.so
library/Demos/SpatialDomains/PartitionAnalyse: /usr/lib/x86_64-linux-gnu/libz.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libtinyxml.a
library/Demos/SpatialDomains/PartitionAnalyse: /usr/lib/x86_64-linux-gnu/liblapack.so
library/Demos/SpatialDomains/PartitionAnalyse: /usr/lib/x86_64-linux-gnu/libblas.so
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libscotch.a
library/Demos/SpatialDomains/PartitionAnalyse: ThirdParty/dist/lib/libscotcherr.a
library/Demos/SpatialDomains/PartitionAnalyse: library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PartitionAnalyse"
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PartitionAnalyse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/build: library/Demos/SpatialDomains/PartitionAnalyse

.PHONY : library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/build

library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/clean:
	cd /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains && $(CMAKE_COMMAND) -P CMakeFiles/PartitionAnalyse.dir/cmake_clean.cmake
.PHONY : library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/clean

library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/depend:
	cd /home/tomas/Documents/gitproject/nektar++/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/Documents/gitproject/nektar++ /home/tomas/Documents/gitproject/nektar++/library/Demos/SpatialDomains /home/tomas/Documents/gitproject/nektar++/build2 /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains /home/tomas/Documents/gitproject/nektar++/build2/library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : library/Demos/SpatialDomains/CMakeFiles/PartitionAnalyse.dir/depend

