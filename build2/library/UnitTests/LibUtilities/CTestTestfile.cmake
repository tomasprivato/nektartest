# CMake generated Testfile for 
# Source directory: /home/tomas/Documents/gitproject/nektar++/library/UnitTests/LibUtilities
# Build directory: /home/tomas/Documents/gitproject/nektar++/build2/library/UnitTests/LibUtilities
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(LibUtilitiesUnitTests "/home/tomas/Documents/gitproject/nektar++/build2/library/UnitTests/LibUtilities/LibUtilitiesUnitTests" "--detect_memory_leaks=0")
set_tests_properties(LibUtilitiesUnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/tomas/Documents/gitproject/nektar++/library/UnitTests/LibUtilities/CMakeLists.txt;22;ADD_TEST;/home/tomas/Documents/gitproject/nektar++/library/UnitTests/LibUtilities/CMakeLists.txt;0;")
subdirs("LinearAlgebra")
