#ifndef MYLIB_H
#define MYLIB_H

void foo();

template <typename TFloat>
bool exactlyEqual(TFloat lhs, TFloat rhs)
{
    // Pragma required for internal code using this header
    // External clients won't see the error due to this being treated as
    // a system include
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
    return lhs == rhs;
#pragma clang diagnostic pop
}

#endif
