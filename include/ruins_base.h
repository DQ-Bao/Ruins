#pragma once
#include <stdint.h>

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

typedef enum
{
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_NONE
} LogLevel;

#ifdef DEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define unimplemented(msg) \
    do \
    { \
        fprintf(stderr, "%s:%d: unimplemented: %s\n", __FILE__, __LINE__, msg); \
        abort(); \
    } while (0)

#define unreachable(msg) \
    do \
    { \
        fprintf(stderr, "%s:%d: unreachable: %s\n", __FILE__, __LINE__, msg); \
        abort(); \
    } while (0)

#define rlog(level, ...) \
    do \
    { \
        switch (level) \
        { \
        case LOG_INFO: \
            fprintf(stderr, "[INFO] "); \
            break; \
        case LOG_WARN: \
            fprintf(stderr, "[WARN] "); \
            break; \
        case LOG_ERROR: \
            fprintf(stderr, "[ERROR] "); \
            break; \
        default: \
            unreachable("rlog"); \
        } \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)

#define rassert assert
#else
#define unimplemented(msg)
#define unreachable(msg)
#define rlog(level, ...)
#define rassert
#endif // DEBUG
