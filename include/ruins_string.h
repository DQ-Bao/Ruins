#pragma once
#include "ruins_base.h"

typedef struct
{
    char* data;
    u64   count;
} string_view;

char* str_from_view(string_view sv);
char* str_copy(char* str);
char* str_from_integer(i64 value);
char* str_from_real(f64 value, u32 precision);

string_view sv_from_cstr(char* str);

u8  sv_to_u8(string_view sv);
i8  sv_to_i8(string_view sv);
u16 sv_to_u16(string_view sv);
i16 sv_to_i16(string_view sv);
u32 sv_to_u32(string_view sv);
i32 sv_to_i32(string_view sv);
u64 sv_to_u64(string_view sv);
i64 sv_to_i64(string_view sv);
f32 sv_to_f32(string_view sv);
f64 sv_to_f64(string_view sv);

void sv_trim_begin(string_view* sv);
void sv_trim_end(string_view* sv);
void sv_trim(string_view* sv);

string_view sv_shift_by_delim(string_view* sv, char delim);
string_view sv_sub(string_view sv, u64 begin, u64 end);

b8 sv_has_prefix(string_view sv, string_view prefix);
b8 sv_has_postfix(string_view sv, string_view postfix);
b8 sv_equals(string_view a, string_view b);
