#include <iostream>

// Including as a system header so any warnings should be ignored anyway
#include <mylib/mylib.h>

int main()
{
    float f = 123.0f;
    float f2 = 456.0f;
    exactlyEqual(f, f2);

    //f == f2;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
