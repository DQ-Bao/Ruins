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
    if (!str.data || str.count <= 0) { return 0; }
    u8 result = 0;
    for (u32 i = 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i8 string_to_i8(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    i8 result = 0;
    b8 is_neg = str.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }

    return is_neg ? -result : result;
}

u16 string_to_u16(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    u16 result = 0;
    for (u32 i = 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i16 string_to_i16(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    i16 result = 0;
    b8  is_neg = str.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

u32 string_to_u32(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    u32 result = 0;
    for (u32 i = 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i32 string_to_i32(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    i32 result = 0;
    b8  is_neg = str.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

u64 string_to_u64(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    u64 result = 0;
    for (u32 i = 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i64 string_to_i64(string str)
{
    if (!str.data || str.count <= 0) { return 0; }
    i64 result = 0;
    b8  is_neg = str.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] >= '0' && str.data[i] <= '9') { result = result * 10 + (str.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

f32 string_to_f32(string str)
{
    if (!str.data || str.count <= 0) { return 0.0f; }
    f32 result = 0.0f;
    b8  is_neg = str.data[0] == '-';
    b8  is_dec = false;
    f32 mul    = 0.1f;
    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] == '.') { is_dec = true; }
        else if (str.data[i] >= '0' && str.data[i] <= '9')
        {
            if (!is_dec) { result = result * 10.0f + (f32)(str.data[i] - 48); }
            else
            {
                result = result + (f32)(str.data[i] - 48) * mul;
                mul   /= 10.0f;
            }
        }
        else { return 0.0f; }
    }
    return is_neg ? -result : result;
}

f64 string_to_f64(string str)
{
    if (!str.data || str.count <= 0) { return 0.0; }
    f64 result = 0.0;
    b8  is_neg = str.data[0] == '-';
    b8  is_dec = false;
    f64 mul    = 0.1;
    for (u32 i = is_neg ? 1 : 0; i < str.count; i++)
    {
        if (str.data[i] == '.') { is_dec = true; }
        else if (str.data[i] >= '0' && str.data[i] <= '9')
        {
            if (!is_dec) { result = result * 10.0 + (f64)(str.data[i] - 48); }
            else
            {
                result = result + (f64)(str.data[i] - 48) * mul;
                mul   /= 10.0;
            }
        }
        else { return 0.0; }
    }
    return is_neg ? -result : result;
}

void string_cut(string* str, u64 begin, u64 n)
{
    if (!str || !str->data || str->count <= 0 || n == 0 || begin >= str->count) { return; }
    if (begin + n < str->count)
    {
        if (begin == 0) { str->data += n; }
        else { memmove(str->data + begin, str->data + begin + n, str->count - (begin + n)); }
        str->count -= n;
    }
    else { str->count -= (str->count - begin); }
}

string string_cut_by_delim(string* str, char delim)
{
    string result = { 0 };
    if (!str || !str->data || str->count <= 0) { return result; }
    for (u64 i = 0; i < str->count; i++)
    {
        if (str->data[i] == delim)
        {
            result = string_sub(*str, 0, i);

            str->count -= i + 1;
            str->data  += i + 1;
            return result;
        }
    }
    result = string_copy(*str);

    str->data += str->count;
    str->count = 0;
    return result;
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
    string result = { 0 };
    result.count  = left.count + right.count;
    result.data   = (char*)malloc((result.count + 1) * sizeof(char));

    result.data[result.count] = '\0';
    if (left.data && left.count > 0) { memcpy(result.data, left.data, left.count); }
    if (right.data && right.count > 0) { memcpy(result.data + left.count, right.data, right.count); }
    result.head = result.data;

    return result;
}

b8 string_has_prefix(string str, string prefix)
{
    if (!str.data || !prefix.data || str.count < prefix.count) { return false; }
    return memcmp(str.data, prefix.data, prefix.count) == 0;
}

b8 string_has_postfix(string str, string postfix)
{
    if (!str.data || !postfix.data || str.count < postfix.count) { return false; }
    return memcmp(str.data + (str.count - postfix.count), postfix.data, postfix.count) == 0;
}

b8 string_equals(string a, string b)
{
    return a.data && b.data && a.count == b.count && memcmp(a.data, b.data, a.count) == 0;
}

b8 string_equals_cstr(string a, char* b)
{
    if (!a.data || !b) { return false; }
    u64 count = strlen(b);
    return a.count == count && memcmp(a.data, b, count) == 0;
}
