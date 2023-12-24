set(SOURCE_FILES 
    equation.cpp 
    unif_mesh.cpp 
    problem.cpp
    variable.cpp
    upwind.cpp
    laxwendroff.cpp
)

add_library(mylib_dir_TD2 ${SOURCE_FILES})