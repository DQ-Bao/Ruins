#pragma once
#include "base.h"
#define PI32 3.141592653589793f
#define PI64 3.141592653589793

static inline i32 div_ceil_i32(i32 a, i32 b)
{
    Assert(b != 0);
    return (a + b - 1) / b;
}

static inline u32 div_ceil_u32(u32 a, u32 b)
{
    Assert(b != 0);
    return (a + b - 1) / b;
}
