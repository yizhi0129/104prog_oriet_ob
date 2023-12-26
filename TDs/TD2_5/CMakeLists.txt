cmake_minimum_required(VERSION 3.10)

# set the project name
project(myproject)

# enable modern C++
set(CMAKE_CXX_STANDARD 17)


# add the executable
add_executable(Main.exe main.cpp)
add_executable(Test.exe test.cpp)

# add the library
add_subdirectory(mylib_dir_TD2)
 

target_link_libraries(Main.exe PUBLIC mylib_dir_TD2)
target_link_libraries(Test.exe PUBLIC mylib_dir_TD2)

target_include_directories(Main.exe PUBLIC mylib_dir_TD2)
target_include_directories(Test.exe PUBLIC mylib_dir_TD2)

target_include_directories(Main.exe PRIVATE chps2023/TDs/TD2_5)
target_include_directories(Test.exe PRIVATE chps2023/TDs/TD2_5)

# add tests
enable_testing()
find_package(GTest REQUIRED)

add_test(NAME Test COMMAND Test.exe)
gtest_discover_tests(Test.exe)
