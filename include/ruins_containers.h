#pragma once
#include "ruins_base.h"
#include "ruins_string.h"

typedef enum
{
    CT_DARRAY,
    CT_HASHTABLE
} ContainerType;

typedef struct
{
    string_view key;
    b8          in_used;
} Slot;

typedef struct
{
    u64   capacity;
    u64   count;
    Slot* hash_table;
} ArrayHeader;

#define da_header(arr) ((ArrayHeader*)(arr) - 1)
#define da_cap(arr) ((arr) ? da_header(arr)->capacity : 0)
#define da_count(arr) ((arr) ? da_header(arr)->count : 0)

#define da_create(type) ((type*)_da_resize_if_need(NULL, sizeof(type), 1, CT_DARRAY))
#define da_reserve(type, cap) ((type*)_da_resize_if_need(NULL, sizeof(type), (cap), CT_DARRAY))

#define da_destroy(arr) ((arr) ? (_da_destroy(da_header(arr)), 0) : 0, (arr) = NULL)
#define da_clear(arr) ((arr) ? (da_header(arr)->count = 0) : 0)

#define da_pop_n(arr, n) ((arr) && da_header(arr)->count > (n) ? &(arr)[da_header(arr)->count -= (n)] : NULL)
#define da_pop(arr) da_pop_n(arr, 1)

#define da_del_n(arr, index, n) \
    ((arr) && da_header(arr)->count > (n) \
         ? (_da_move((arr) + (index), (arr) + (index) + (n), sizeof(*(arr)), da_header(arr)->count - (index) - (n)), \
            da_header(arr)->count -= (n)) \
         : da_count(arr))
#define da_del(arr, index) da_del_n(arr, index, 1)

#define da_push_n_empty(arr, n) \
    ((arr) = _da_resize_if_need((arr), sizeof(*(arr)), da_count(arr) + (n), CT_DARRAY), \
     (da_header(arr)->count += (n), &(arr)[da_header(arr)->count - (n)]))
#define da_push(arr, value) ((*da_push_n_empty(arr, 1)) = (value))
#define da_push_n(arr, items, n) (_da_copy(da_push_n_empty((arr), (n)), (items), sizeof(*(arr)), (n)))

#define da_insert_n_empty(arr, index, n) \
    ((arr) = _da_resize_if_need((arr), sizeof(*(arr)), da_count(arr) + (n), CT_DARRAY), da_header(arr)->count += (n), \
     _da_move((arr) + (index) + (n), (arr) + (index), sizeof(*(arr)), da_header(arr)->count - (index) - (n)), \
     &(arr)[(index)])
#define da_insert(arr, index, value) ((*da_insert_n_empty((arr), (index), 1)) = (value))
#define da_insert_n(arr, index, items, n) \
    (_da_copy(da_insert_n_empty((arr), (index), (n)), (items), sizeof(*(arr)), (n)))

void  _da_destroy(void* head);
void* _da_resize_if_need(void* arr, u64 stride, u64 new_capacity, ContainerType type);
void  _da_copy(void* dest, void* items, u64 stride, u64 count);
void  _da_move(void* dest, void* items, u64 stride, u64 count);
u64   _ht_put_helper(void* table, string_view key);
u64   _ht_get_hash(void* table, string_view key);

#define ht_header da_header
#define ht_cap da_cap
#define ht_count da_count
#define ht_create(type) ((type*)_da_resize_if_need(NULL, sizeof(type), 1000 * 1000, CT_HASHTABLE))
#define ht_put(table, key, value) ((table)[_ht_put_helper((table), (key))] = (value))
#define ht_get(table, key) (&(table)[_ht_get_hash((table), (key))])
#define ht_del(table, key) \
    (ht_header(table)->hash_table[_ht_get_hash((table), (key))].in_used = false, --ht_header(table)->count)
