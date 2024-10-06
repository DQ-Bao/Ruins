#pragma once
#include "ruins_base.h"

// TODO: May be make a memory pool for the strings to avoid too many mallocs

typedef struct
{
    u64   count;
    char* head;
    char* data;
} string;

string string_from_cstr(char* str);
void   string_free(string* str);
string string_copy(string str);

string string_from_u8(u8 value);
string string_from_i8(i8 value);
string string_from_u16(u16 value);
string string_from_i16(i16 value);
string string_from_u32(u32 value);
string string_from_i32(i32 value);
string string_from_u64(u64 value);
string string_from_i64(i64 value);
string string_from_f32(f32 value, u32 precision);
string string_from_f64(f64 value, u32 precision);

u8  string_to_u8(string str);
i8  string_to_i8(string str);
u16 string_to_u16(string str);
i16 string_to_i16(string str);
u32 string_to_u32(string str);
i32 string_to_i32(string str);
u64 string_to_u64(string str);
i64 string_to_i64(string str);
f32 string_to_f32(string str);
f64 string_to_f64(string str);

void string_trim_begin(string* str);
void string_trim_end(string* str);
void string_trim(string* str);

void   string_cut(string* str, u64 begin, u64 n);
string string_cut_by_delim(string* str, char delim);

string string_sub(string str, u64 begin, u64 end);
string string_concat(string left, string right);

b8 string_has_prefix(string str, string prefix);
b8 string_has_postfix(string str, string postfix);
b8 string_equals(string a, string b);
b8 string_equals_cstr(string a, char* b);
