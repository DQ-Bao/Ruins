#include "ruins_string.h"
#include "ruins_base.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string string_from_cstr(char* str)
{
    string result = { 0 };
    result.count  = strlen(str);
    result.head   = str;
    result.data   = str;
    return result;
}

void string_free(string* str)
{
    if (str && str->head)
    {
        str->count = 0;
        free(str->head);
        str->head = 0;
        str->data = 0;
    }
}

string string_copy(string str)
{
    string result = { 0 };
    result.count  = str.count;
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    memcpy(result.data, str.data, result.count + 1);
    result.head = result.data;
    return result;
}

string string_from_u8(u8 value)
{
    string result = { 0 };
    result.count  = 1;
    result.data   = (char*)malloc(2 * sizeof(char));
    if (!result.data) { return result; }
    result.data[0] = (char)value;
    result.data[1] = '\0';
    result.head    = result.data;
    return result;
}

string string_from_i8(i8 value)
{
    if (value >= 0) { return string_from_u8((u8)value); }

    string result = { 0 };
    result.count  = 2;
    result.data   = (char*)malloc(3 * sizeof(char));
    if (!result.data) { return result; }

    result.data[0] = '-';
    result.data[1] = (char)(-value);
    result.data[2] = '\0';
    result.head    = result.data;
    return result;
}

string string_from_u16(u16 value)
{
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%hu", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%hu", value);
    result.head = result.data;
    return result;
}

string string_from_i16(i16 value)
{
    if (value >= 0) { return string_from_u16(value); }
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%hd", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%hd", value);
    result.head = result.data;
    return result;
}

string string_from_u32(u32 value)
{
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%u", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%u", value);
    result.head = result.data;
    return result;
}

string string_from_i32(i32 value)
{
    if (value >= 0) { return string_from_u32(value); }
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%d", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%d", value);
    result.head = result.data;
    return result;
}

string string_from_u64(u64 value)
{
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%llu", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%llu", value);
    result.head = result.data;
    return result;
}

string string_from_i64(i64 value)
{
    if (value >= 0) { return string_from_u64(value); }
    string result = { 0 };
    result.count  = snprintf(NULL, 0, "%lld", value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, "%lld", value);
    result.head = result.data;
    return result;
}

string string_from_f32(f32 value, u32 precision)
{
    char format[10];
    snprintf(format, sizeof(format), "%%.%uf", precision);
    string result = { 0 };
    result.count  = snprintf(NULL, 0, format, value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, format, value);
    result.head = result.data;
    return result;
}

string string_from_f64(f64 value, u32 precision)
{
    char format[10];
    snprintf(format, sizeof(format), "%%.%uf", precision);
    string result = { 0 };
    result.count  = snprintf(NULL, 0, format, value);
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));
    if (!result.data) { return result; }
    snprintf(result.data, result.count + 1, format, value);
    result.head = result.data;
    return result;
}

void string_trim_begin(string* str)
{
    if (!str || !str->data || str->count <= 0) { return; }
    while (str->count != 0 && isspace(*str->data))
    {
        str->data++;
        str->count--;
    }
}

void string_trim_end(string* str)
{
    if (!str || !str->data || str->count <= 0) { return; }
    while (str->count != 0 && isspace(*(str->data + str->count - 1)))
    {
        str->count--;
        str->data[str->count] = '\0';
    }
}

void string_trim(string* str)
{
    string_trim_begin(str);
    string_trim_end(str);
}

u8 string_to_u8(string str)
{
    unimplemented("");
}

i8 string_to_i8(string str)
{
    unimplemented("");
}

u16 string_to_u16(string str)
{
    unimplemented("");
}

i16 string_to_i16(string str)
{
    unimplemented("");
}

u32 string_to_u32(string str)
{
    unimplemented("");
}

i32 string_to_i32(string str)
{
    unimplemented("");
}

u64 string_to_u64(string str)
{
    unimplemented("");
}

i64 string_to_i64(string str)
{
    unimplemented("");
}

f32 string_to_f32(string str)
{
    unimplemented("");
}

f64 string_to_f64(string str)
{
    unimplemented("");
}

void string_cut_begin(string* str, u64 n)
{
    unimplemented("");
}

void string_cut_end(string* str, u64 n)
{
    unimplemented("");
}

void string_cut(string* str, u64 begin, u64 end)
{
    unimplemented("");
}

string string_cut_from_delim(string* str, char delim)
{
    string result = { 0 };
    if (!str || !str->data || str->count <= 0) { return result; }
    for (u64 i = 0; i < str->count; i++)
    {
        if (str->data[i] == delim)
        {
            result.count = i;
            result.data  = (char*)malloc((i + 1) * sizeof(char));

            result.data[result.count] = '\0';

            str->count -= i + 1;
            memcpy(result.data, str->data, result.count);
            result.head = result.data;
            str->data  += i + 1;
            return result;
        }
    }
    return string_copy(*str);
}

string string_sub(string str, u64 begin, u64 end)
{
    string result = { 0 };
    if (!str.data || str.count <= 0 || begin > end) { return result; }

    result.count = end - begin;
    result.data  = (char*)malloc((result.count + 1) * sizeof(char));

    result.data[result.count] = '\0';
    if (result.count > 0) { memcpy(result.data, str.data + begin, result.count); }
    result.head = result.data;
    return result;
}

string string_concat(string left, string right)
{
    unimplemented("");
}

b8 string_has_prefix(string str, string prefix)
{
    unimplemented("");
}

b8 string_has_postfix(string str, string postfix)
{
    unimplemented("");
}

b8 string_equals(string a, string b)
{
    return a.count == b.count && memcmp(a.data, b.data, a.count) == 0;
}

b8 string_equals_cstr(string a, char* b)
{
    u64 count = strlen(b);
    return a.count == count && memcmp(a.data, b, count) == 0;
}
