#include "ruins_containers.h"
#include <stdlib.h>
#include <string.h>

DynamicArray _darray_create(u64 count, u64 stride)
{
    DynamicArray arr = { 0 };
    arr.capacity     = count;
    arr.stride       = stride;
    if (count > 0) { arr.data = malloc(count * stride); }
    arr.head = arr.data;
    return arr;
}

void _darray_destroy(DynamicArray* arr)
{
    if (arr->head) { free(arr->head); }
}

static void _darray_expand(DynamicArray* arr)
{
    if (arr->head != arr->data) { memmove(arr->head, arr->data, arr->count); }
    u64 new_capacity = arr->head ? 2 * arr->count : 256;
    u64 size         = new_capacity * arr->stride;
    arr->head        = realloc(arr->head, size);
    arr->data        = arr->head;
    arr->capacity    = new_capacity;
}

void _darray_clear(DynamicArray* arr)
{
    arr->count = 0;
}

void _darray_push_start(DynamicArray* arr, void* value)
{
    while (arr->count + 1 > arr->capacity)
    {
        _darray_expand(arr);
    }
    memmove((u8*)arr->data + arr->stride, arr->data, arr->count * arr->stride);
    memcpy(arr->data, value, arr->stride);
    arr->count++;
}

void _darray_push_end(DynamicArray* arr, void* value)
{
    while (arr->count + 1 > arr->capacity)
    {
        _darray_expand(arr);
    }
    memcpy((u8*)arr->data + (arr->count * arr->stride), value, arr->stride);
    arr->count++;
}

void _darray_concat(DynamicArray* arr, void* items, u64 count)
{
    while (arr->count + count > arr->capacity)
    {
        _darray_expand(arr);
    }
    memcpy((u8*)arr->data + (arr->count * arr->stride), items, count * arr->stride);
    arr->count += count;
}

void* _darray_pop_start(DynamicArray* arr)
{
    if (!arr->data || arr->count < 1) { return NULL; }
    void* head = arr->data;
    arr->data  = (u8*)arr->data + arr->stride;
    arr->count--;
    return head;
}

void* _darray_pop_end(DynamicArray* arr)
{
    if (!arr->data || arr->count < 1) { return NULL; }
    arr->count--;
    return (void*)((u8*)arr->data + (arr->count * arr->stride));
}

void* _darray_get(DynamicArray* arr, u64 index)
{
    if (!arr->data || arr->count < 1) { return NULL; }
    return (void*)((u8*)arr->data + (index * arr->stride));
}
