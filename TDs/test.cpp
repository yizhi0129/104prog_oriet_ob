#include "gtest/gtest.h"
#include "mylib_dir/mylib.h"

// This macro creates a test case MylibTestPrintTest, of type UnitTest
TEST(UnitTest, MylibTestPrintTest)
{ 
  MyLib::MyClass myclass;
  myclass.print();
  // Create an instance of Mylib::MyClass and test print method
}



