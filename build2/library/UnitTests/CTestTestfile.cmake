# CMake generated Testfile for 
# Source directory: /home/tomas/Documents/gitproject/nektar++/library/UnitTests
# Build directory: /home/tomas/Documents/gitproject/nektar++/build2/library/UnitTests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "/home/tomas/Documents/gitproject/nektar++/build2/library/UnitTests/UnitTests" "--detect_memory_leaks=0")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/tomas/Documents/gitproject/nektar++/library/UnitTests/CMakeLists.txt;20;ADD_TEST;/home/tomas/Documents/gitproject/nektar++/library/UnitTests/CMakeLists.txt;0;")
subdirs("LibUtilities")
subdirs("LocalRegions")
subdirs("Collections")
