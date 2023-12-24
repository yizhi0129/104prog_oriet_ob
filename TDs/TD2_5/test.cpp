#include "gtest/gtest.h"
#include "mylib_dir_TD2/unif_mesh.h"
#include "mylib_dir_TD2/problem.h"
#include "mylib_dir_TD2/equation.h"

TEST(UnitaryTest, MeshTest)
{
    // Create an instance of UniformMesh
    UniformMesh mesh(0.0, 1.0, 0.1, 0.0, 5.0, 0.5);

    // Test individual functions
    EXPECT_DOUBLE_EQ(mesh.initial_time(), 0.0);
    EXPECT_DOUBLE_EQ(mesh.final_time(), 1.0);
    EXPECT_DOUBLE_EQ(mesh.time_step(), 0.1);
    EXPECT_DOUBLE_EQ(mesh.initial_position(), 0.0);
    EXPECT_DOUBLE_EQ(mesh.final_position(), 5.0);
    EXPECT_DOUBLE_EQ(mesh.position_step(), 0.5);

    
    EXPECT_EQ(mesh.x_size(), 11);  
    EXPECT_EQ(mesh.t_size(), 11);  
    

    EXPECT_DOUBLE_EQ(mesh.x_i(0), 0.0);
    EXPECT_DOUBLE_EQ(mesh.x_i(1), 0.5);
    EXPECT_DOUBLE_EQ(mesh.x_i(2), 1.0);
    EXPECT_DOUBLE_EQ(mesh.x_i(3), 1.5);
    EXPECT_DOUBLE_EQ(mesh.x_i(4), 2.0);
    EXPECT_DOUBLE_EQ(mesh.x_i(5), 2.5);
    EXPECT_DOUBLE_EQ(mesh.x_i(6), 3.0);
    EXPECT_DOUBLE_EQ(mesh.x_i(7), 3.5);
    EXPECT_DOUBLE_EQ(mesh.x_i(8), 4.0);
    EXPECT_DOUBLE_EQ(mesh.x_i(9), 4.5);
    EXPECT_DOUBLE_EQ(mesh.x_i(10), 5.0);

    EXPECT_DOUBLE_EQ(mesh.t_n(0), 0.0);
    EXPECT_DOUBLE_EQ(mesh.t_n(1), 0.1);
    EXPECT_DOUBLE_EQ(mesh.t_n(2), 0.2);
    EXPECT_DOUBLE_EQ(mesh.t_n(3), 0.3);
    EXPECT_DOUBLE_EQ(mesh.t_n(4), 0.4);
    EXPECT_DOUBLE_EQ(mesh.t_n(5), 0.5);
    EXPECT_DOUBLE_EQ(mesh.t_n(6), 0.6);
    EXPECT_DOUBLE_EQ(mesh.t_n(7), 0.7);
    EXPECT_DOUBLE_EQ(mesh.t_n(8), 0.8);
    EXPECT_DOUBLE_EQ(mesh.t_n(9), 0.9);
    EXPECT_DOUBLE_EQ(mesh.t_n(10), 1.0);
}

TEST(UnitaryTest,ProblemTest)
{
  // construction et test d'une instance de Problem
}

TEST(MainFunctionTest,EquationTest)
{
  // construction et test d'une instance de Equation
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}