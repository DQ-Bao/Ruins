#pragma once
#include "ruins_base.h"

typedef struct
{
    u64   capacity;
    u64   count;
    u64   stride;
    void* head;
    void* data;
} DynamicArray;

#define darray_create(type) _darray_create(0, sizeof(type))
#define darray_reserve(type, capacity) _darray_create(capacity, sizeof(type))
#define darray_destroy(arr) _darray_destroy(arr)
#define darray_clear(arr) _darray_clear(arr)
#define darray_push_start(type, arr, value) \
    { \
        type temp = value; \
        _darray_push_start(arr, &temp); \
    }
#define darray_push_end(type, arr, value) \
    { \
        type temp = value; \
        _darray_push_end(arr, &temp); \
    }
#define darray_concat(arr, items, count) _darray_concat(arr, items, count)
#define darray_pop_start(type, arr) (type*)_darray_pop_start(arr)
#define darray_pop_end(type, arr) (type*)_darray_pop_end(arr)
#define darray_get(type, arr, index) (type*)_darray_get(arr, index)
// NOTE: can not use rvalue for value
#define darray_find(type, arr, value) (type*)_darray_find(arr, &value)

DynamicArray _darray_create(u64 capacity, u64 stride);
void         _darray_destroy(DynamicArray* arr);
void         _darray_clear(DynamicArray* arr);
void         _darray_push_start(DynamicArray* arr, void* value);
void         _darray_push_end(DynamicArray* arr, void* value);
void         _darray_concat(DynamicArray* arr, void* items, u64 count);
void*        _darray_pop_start(DynamicArray* arr);
void*        _darray_pop_end(DynamicArray* arr);
void*        _darray_get(DynamicArray* arr, u64 index);
void*        _darray_find(DynamicArray* arr, void* value);
