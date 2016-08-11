// Include as user (non-system) header, hence the need for the pragma
#include "include/mylib/mylib.h"

void foo()
{
    float f = 123.0f;
    float f2 = 456.0f;
    exactlyEqual(f, f2);
}
