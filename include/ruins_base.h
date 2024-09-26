#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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
typedef _Bool    b8;
#define false 0
#define true 1

#define Kilobytes(value) ((value) * 1024)
#define Megabytes(value) (Kilobytes(value) * 1024)
#define Gigabytes(value) (Megabytes(value) * 1024)
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GAME_FPS 60

#define panic(...) \
    { \
        fprintf(stderr, __VA_ARGS__); \
        exit(1); \
    }
#define unimplemented(...) \
    { \
        panic("Unimplemented: %s", __VA_ARGS__); \
    }

#ifdef DEBUG
#define rerror(...) \
    { \
        fprintf(stderr, "%s: In function '%s':\n", __FILE__, __func__); \
        fprintf(stderr, "%s:%d: error: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
        abort(); \
    }

#define rwarn(...) \
    { \
        fprintf(stderr, "%s: In function '%s':\n", __FILE__, __func__); \
        fprintf(stderr, "%s:%d: warning: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    }

#define rlog(...) \
    { \
        fprintf(stdout, __VA_ARGS__); \
        fprintf(stdout, "\n"); \
    }

#define rassert(x) \
    { \
        if (!(x)) \
        { \
            fprintf(stderr, "%s: In function '%s':\n", __FILE__, __func__); \
            fprintf(stderr, "%s:%d: assertion failed:\n", __FILE__, __LINE__); \
            fprintf(stderr, "%4d | %s\n", __LINE__, #x); \
            abort(); \
        } \
    }
#define rassert_msg(x, ...) \
    { \
        if (!(x)) \
        { \
            fprintf(stderr, "%s: In function '%s':\n", __FILE__, __func__); \
            fprintf(stderr, "%s:%d: assertion failed: ", __FILE__, __LINE__); \
            fprintf(stderr, __VA_ARGS__); \
            fprintf(stderr, "\n%4d | %s\n", __LINE__, #x); \
            abort(); \
        } \
    }
#else
#define rerror(...)
#define rwarn(...)
#define rlog(...)
#define rassert(x)
#define rassert_msg(x, ...)
#endif // DEBUG
