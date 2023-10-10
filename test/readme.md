### unit tests

diy framework because I can and linking GTest on three different platforms was more work than rolling my own

## implementing unit tests

# create .h file

create a test class header file such as the below

#include "../framework/testbase.h"
UNIT_TEST_CLASS(MyUnitTests)

# create .cpp file

add a .cpp implementation. in that file, create a bunch of unit tests in the form

bool my_unit_test() {
    return true;
}

# register the tests

implement the register_tests method in the cpp file. each individual unit test should be registered with the macro UNIT_TEST(..)

void MyUnitTests::register_tests() {
    UNIT_TEST(my_unit_test);
}

in TestFactory.cpp, add the category for thetest class
in CMakeLists.txt add the test category to run
