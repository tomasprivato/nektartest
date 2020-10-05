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
include solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/depend.make

# Include the progress variables for this target.
include solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/progress.make

# Include the compile flags for this target's objects.
include solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/flags.make

solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o: solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/flags.make
solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o: ../solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o -c /home/tomas/Documents/gitproject/nektar++/solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld.cpp

solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.i"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/Documents/gitproject/nektar++/solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld.cpp > CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.i

solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.s"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/Documents/gitproject/nektar++/solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld.cpp -o CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.s

# Object files for target AddModeTo2DFld
AddModeTo2DFld_OBJECTS = \
"CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o"

# External object files for target AddModeTo2DFld
AddModeTo2DFld_EXTERNAL_OBJECTS =

solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/AddModeTo2DFld.cpp.o
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/build.make
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/SolverUtils/libSolverUtils.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/FieldUtils/libFieldUtils.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/GlobalMapping/libGlobalMapping.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/MultiRegions/libMultiRegions.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/Collections/libCollections.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/LocalRegions/libLocalRegions.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/SpatialDomains/libSpatialDomains.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/StdRegions/libStdRegions.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: library/LibUtilities/libLibUtilities.so.5.0.0
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libboost_thread.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libboost_iostreams.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libboost_program_options.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libboost_filesystem.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libboost_system.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: /usr/lib/x86_64-linux-gnu/libz.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libtinyxml.a
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libblas.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/liblapack.so
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libscotch.a
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: ThirdParty/dist/lib/libscotcherr.a
solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld: solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/Documents/gitproject/nektar++/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AddModeTo2DFld"
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AddModeTo2DFld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/build: solvers/IncNavierStokesSolver/Utilities/AddModeTo2DFld

.PHONY : solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/build

solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/clean:
	cd /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities && $(CMAKE_COMMAND) -P CMakeFiles/AddModeTo2DFld.dir/cmake_clean.cmake
.PHONY : solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/clean

solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/depend:
	cd /home/tomas/Documents/gitproject/nektar++/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/Documents/gitproject/nektar++ /home/tomas/Documents/gitproject/nektar++/solvers/IncNavierStokesSolver/Utilities /home/tomas/Documents/gitproject/nektar++/build2 /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities /home/tomas/Documents/gitproject/nektar++/build2/solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : solvers/IncNavierStokesSolver/Utilities/CMakeFiles/AddModeTo2DFld.dir/depend

