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
include solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/depend.make

# Include the progress variables for this target.
include solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/progress.make

# Include the compile flags for this target's objects.
include solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/flags.make

solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o: solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/flags.make
solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o: ../solvers/DiffusionSolver/DiffusionSolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o -c /home/tomas/Documents/gitproject/nektar++/solvers/DiffusionSolver/DiffusionSolver.cpp

solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.i"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/Documents/gitproject/nektar++/solvers/DiffusionSolver/DiffusionSolver.cpp > CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.i

solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.s"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/Documents/gitproject/nektar++/solvers/DiffusionSolver/DiffusionSolver.cpp -o CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.s

# Object files for target DiffusionSolver
DiffusionSolver_OBJECTS = \
"CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o"

# External object files for target DiffusionSolver
DiffusionSolver_EXTERNAL_OBJECTS =

solvers/DiffusionSolver/DiffusionSolver: solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DiffusionSolver.cpp.o
solvers/DiffusionSolver/DiffusionSolver: solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/build.make
solvers/DiffusionSolver/DiffusionSolver: library/SolverUtils/libSolverUtils.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/FieldUtils/libFieldUtils.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/GlobalMapping/libGlobalMapping.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/MultiRegions/libMultiRegions.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/Collections/libCollections.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/LocalRegions/libLocalRegions.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/SpatialDomains/libSpatialDomains.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/StdRegions/libStdRegions.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: library/LibUtilities/libLibUtilities.so.5.0.0
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libboost_thread.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libboost_iostreams.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libboost_program_options.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libboost_filesystem.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libboost_system.so
solvers/DiffusionSolver/DiffusionSolver: /usr/lib/x86_64-linux-gnu/libz.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libtinyxml.a
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libblas.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/liblapack.so
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libscotch.a
solvers/DiffusionSolver/DiffusionSolver: ThirdParty/dist/lib/libscotcherr.a
solvers/DiffusionSolver/DiffusionSolver: solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DiffusionSolver"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DiffusionSolver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/build: solvers/DiffusionSolver/DiffusionSolver

.PHONY : solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/build

solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/clean:
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver && $(CMAKE_COMMAND) -P CMakeFiles/DiffusionSolver.dir/cmake_clean.cmake
.PHONY : solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/clean

solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/depend:
	cd /home/tomas/Documents/gitproject/nektar++/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/Documents/gitproject/nektar++ /home/tomas/Documents/gitproject/nektar++/solvers/DiffusionSolver /home/tomas/Documents/gitproject/nektar++/build2 /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver /home/tomas/Documents/gitproject/nektar++/build2/solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : solvers/DiffusionSolver/CMakeFiles/DiffusionSolver.dir/depend

