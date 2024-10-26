#include "ruins_string.h"
#include "ruins_base.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_view sv_from_cstr(char* str)
{
    string_view view = { 0 };
    view.count       = strlen(str);
    view.data        = str;
    return view;
}

char* str_from_view(string_view sv)
{
    char* result     = (char*)malloc((sv.count + 1) * sizeof(char));
    result[sv.count] = '\0';
    if (sv.data) { memcpy(result, sv.data, sv.count); }
    return result;
}

char* str_copy(char* str)
{
    if (!str) { return str; }
    i32   len    = strlen(str);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    strcpy(result, str);
    return result;
}

char* str_from_integer(i64 value)
{
    i32   len    = snprintf(NULL, 0, "%lld", value);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) { return result; }
    snprintf(result, len + 1, "%lld", value);
    return result;
}

char* str_from_real(f64 value, u32 precision)
{
    char format[10];
    snprintf(format, sizeof(format), "%%.%uf", precision);
    i32   len    = snprintf(NULL, 0, format, value);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) { return result; }
    snprintf(result, len + 1, format, value);
    return result;
}

void sv_trim_begin(string_view* sv)
{
    if (!sv || !sv->data || sv->count <= 0) { return; }
    while (sv->count != 0 && isspace(*sv->data))
    {
        sv->data++;
        sv->count--;
    }
}

void sv_trim_end(string_view* sv)
{
    if (!sv || !sv->data || sv->count <= 0) { return; }
    while (sv->count != 0 && isspace(*(sv->data + sv->count - 1)))
    {
        sv->count--;
        sv->data[sv->count] = '\0';
    }
}

void sv_trim(string_view* sv)
{
    sv_trim_begin(sv);
    sv_trim_end(sv);
}

u8 sv_to_u8(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    u8 result = 0;
    for (u32 i = 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i8 sv_to_i8(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    i8 result = 0;
    b8 is_neg = sv.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }

    return is_neg ? -result : result;
}

u16 sv_to_u16(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    u16 result = 0;
    for (u32 i = 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i16 sv_to_i16(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    i16 result = 0;
    b8  is_neg = sv.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

u32 sv_to_u32(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    u32 result = 0;
    for (u32 i = 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i32 sv_to_i32(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    i32 result = 0;
    b8  is_neg = sv.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

u64 sv_to_u64(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    u64 result = 0;
    for (u32 i = 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return result;
}

i64 sv_to_i64(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0; }
    i64 result = 0;
    b8  is_neg = sv.data[0] == '-';

    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] >= '0' && sv.data[i] <= '9') { result = result * 10 + (sv.data[i] - 48); }
        else { return 0; }
    }
    return is_neg ? -result : result;
}

f32 sv_to_f32(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0.0f; }
    f32 result = 0.0f;
    b8  is_neg = sv.data[0] == '-';
    b8  is_dec = false;
    f32 mul    = 0.1f;
    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] == '.') { is_dec = true; }
        else if (sv.data[i] >= '0' && sv.data[i] <= '9')
        {
            if (!is_dec) { result = result * 10.0f + (f32)(sv.data[i] - 48); }
            else
            {
                result = result + (f32)(sv.data[i] - 48) * mul;
                mul   /= 10.0f;
            }
        }
        else { return 0.0f; }
    }
    return is_neg ? -result : result;
}

f64 sv_to_f64(string_view sv)
{
    if (!sv.data || sv.count <= 0) { return 0.0; }
    f64 result = 0.0;
    b8  is_neg = sv.data[0] == '-';
    b8  is_dec = false;
    f64 mul    = 0.1;
    for (u32 i = is_neg ? 1 : 0; i < sv.count; i++)
    {
        if (sv.data[i] == '.') { is_dec = true; }
        else if (sv.data[i] >= '0' && sv.data[i] <= '9')
        {
            if (!is_dec) { result = result * 10.0 + (f64)(sv.data[i] - 48); }
            else
            {
                result = result + (f64)(sv.data[i] - 48) * mul;
                mul   /= 10.0;
            }
        }
        else { return 0.0; }
    }
    return is_neg ? -result : result;
}

string_view sv_shift_by_delim(string_view* sv, char delim)
{
    string_view result = { 0 };
    if (!sv || !sv->data || sv->count <= 0) { return result; }

    result.data = sv->data;
    for (u64 i = 0; sv->count > 0 && sv->data[i] != delim; i++)
    {
        result.count++;
        sv->count--;
    }
    if (sv->count > 0) { sv->count--; } // Skip the delim
    sv->data += result.count + 1;
    return result;
}

string_view sv_sub(string_view sv, u64 begin, u64 end)
{
    string_view result = { 0 };
    if (!sv.data || sv.count <= 0 || begin > end) { return result; }

    result.count = end - begin;
    result.data  = sv.data + begin;
    return result;
}

b8 sv_has_prefix(string_view sv, string_view prefix)
{
    if (!sv.data || !prefix.data || sv.count < prefix.count) { return false; }
    return memcmp(sv.data, prefix.data, prefix.count) == 0;
}

b8 sv_has_postfix(string_view sv, string_view postfix)
{
    if (!sv.data || !postfix.data || sv.count < postfix.count) { return false; }
    return memcmp(sv.data + (sv.count - postfix.count), postfix.data, postfix.count) == 0;
}

b8 sv_equals(string_view a, string_view b)
{
    return a.data && b.data && a.count == b.count && memcmp(a.data, b.data, a.count) == 0;
}
