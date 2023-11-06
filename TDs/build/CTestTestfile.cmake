# CMake generated Testfile for 
# Source directory: /home/yyz/文档/chps2023/TDs
# Build directory: /home/yyz/文档/chps2023/TDs/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test.cpp "Main.exe")
set_tests_properties(Test.cpp PROPERTIES  _BACKTRACE_TRIPLES "/home/yyz/文档/chps2023/TDs/CMakeLists.txt;31;add_test;/home/yyz/文档/chps2023/TDs/CMakeLists.txt;0;")
subdirs("mylib_dir")
