# to compile
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# to execute the program
./Main.exe t_init t_final dt x_min x_max dx option
t_init t_final dt x_min x_max dx: 
double values: 0 1 0.5 0 5 2 or 0 2 0.1 0 10 0.1 or 0 10 0.1 0 10 1e-6
option: 
string: "solve", "solve_parallel", "solve_async" 

# to test
./Test.exe

# to plot
gunplot plot.gp