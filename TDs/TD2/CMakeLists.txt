cmake_minimum_required(VERSION 3.10)

# set the project name
project(myproject)

# enable modern C++
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(my_executable/Main.exe main.cpp)
add_executable(my_executable/Equation.exe equation.cpp)
add_executable(my_executable/Imesh.exe imesh.cpp)
add_executable(my_executable/Problem.exe problem.cpp)
add_executable(my_executable/Unif_mesh.exe unif_mesh.cpp)


target_include_directories(Main.exe PRIVATE chps2023/TDs/TD2/my_executable)

