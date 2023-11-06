cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)

# enable modern C++
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

# add the executable
add_executable(Main.exe main.cpp)
add_executable(Test.exe test.cpp)


# add library
add_subdirectory(mylib_dir)
 

target_link_libraries(Main.exe PUBLIC mylib)
target_include_directories(Main.exe PUBLIC mylib_dir)


target_link_libraries(Test.exe PUBLIC GTest::GTest)
target_link_libraries(Test.exe PUBLIC GTest::Main)
target_link_libraries(Test.exe PUBLIC mylib)
target_include_directories(Test.exe PUBLIC mylib_dir)


enable_testing()
add_test(Test.cpp Main.exe)
