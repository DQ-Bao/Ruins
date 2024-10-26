#include "ruins_containers.h"
#include "ruins_base.h"
#include <stdlib.h>
#include <string.h>

void _da_destroy(void* head)
{
    if (((ArrayHeader*)head)->hash_table) { free(((ArrayHeader*)head)->hash_table); }
    free(head);
}

void* _da_resize_if_need(void* arr, u64 stride, u64 new_capacity, ContainerType type)
{
    if (new_capacity < da_cap(arr)) { return arr; }
    if (new_capacity < 2 * da_cap(arr)) { new_capacity = 2 * da_cap(arr); }

    u64   size   = stride * new_capacity + sizeof(ArrayHeader);
    void* result = realloc((arr) ? da_header(arr) : NULL, size);
    result       = (u8*)result + sizeof(ArrayHeader);

    if (!arr)
    {
        da_header(result)->count      = 0;
        da_header(result)->hash_table = NULL;
    }
    da_header(result)->capacity = new_capacity;
    if (type == CT_HASHTABLE)
    {
        da_header(result)->hash_table = realloc(da_header(result)->hash_table, new_capacity * sizeof(Slot));
    }
    return result;
}

void _da_copy(void* dest, void* items, u64 stride, u64 count)
{
    if (!dest || !items) { return; }
    if (count == 0 || stride == 0) { return; }
    memcpy(dest, items, count * stride);
}

void _da_move(void* dest, void* items, u64 stride, u64 count)
{
    if (!dest || !items) { return; }
    if (count == 0 || stride == 0) { return; }
    memmove(dest, items, count * stride);
}

static u64 _ht_hash_djb2(void* data, u64 size)
{
    u64 hash  = 5381;
    u8* bytes = (u8*)data;
    for (u32 i = 0; i < size; i++)
    {
        hash = ((hash << 5) + hash) + bytes[i];
    }
    return hash;
}

u64 _ht_get_hash(void* table, string_view key)
{
    u64 hash = _ht_hash_djb2(key.data, key.count) % ht_header(table)->capacity;
    for (u64 i = 0; i < ht_header(table)->capacity && !sv_equals(key, ht_header(table)->hash_table[hash].key); i++)
    {
        hash = (hash + 1) % ht_header(table)->capacity;
    }
    if (sv_equals(key, ht_header(table)->hash_table[hash].key)) { return hash; }
    rlog(LOG_ERROR, "Hash table item not found");
    abort();
}

u64 _ht_put_helper(void* table, string_view key)
{
    u64 hash = _ht_hash_djb2(key.data, key.count) % ht_header(table)->capacity;
    for (u64 i = 0; i < ht_header(table)->capacity && ht_header(table)->hash_table[hash].in_used &&
                    !sv_equals(key, ht_header(table)->hash_table[hash].key);
         i++)

    {
        hash = (hash + 1) % ht_header(table)->capacity;
    }

    if (ht_header(table)->hash_table[hash].in_used)
    {
        if (sv_equals(key, ht_header(table)->hash_table[hash].key)) { return hash; }
        else
        {
            rlog(LOG_ERROR, "Hash table overflow");
            abort();
        }
    }
    else
    {
        ht_header(table)->hash_table[hash].in_used = true;
        ht_header(table)->hash_table[hash].key     = key;
        ht_header(table)->count++;
        return hash;
    }
}
