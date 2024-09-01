#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;
typedef float    f32;
typedef double   f64;
typedef size_t   memidx;
typedef _Bool    b8;

#define false 0
#define true 1
#define Kilobytes(value) ((value) * 1024)
#define Megabytes(value) (Kilobytes(value) * 1024)
#define Gigabytes(value) (Megabytes(value) * 1024)

#ifdef DEBUG
#define Assert(x) \
    { \
        if (!(x)) { abort(); } \
    }
#else
#define Assert(x)
#endif
