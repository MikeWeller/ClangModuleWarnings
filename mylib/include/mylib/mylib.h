#ifndef MYLIB_H
#define MYLIB_H

void foo();

template <typename TFloat>
bool exactlyEqual(TFloat lhs, TFloat rhs)
{
    // Pragma required for internal code using this header
    // External clients shouldn't see the error due to this being treated as
    // a system include and us using -Wno-system-headers
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
    return lhs == rhs;
#pragma clang diagnostic pop
}

void bar();
inline void bar()
{
    int* i;
    // I want to see a warning here when building mylib, but not clients
    *i = 123;
}

#endif
