#pragma once
#include "ruins_string.h"

typedef struct
{
    string_view name;
    string_view type;
    string_view value;
} AssetConfig;

string_view  file_read_to_string(char** buffer, char* filepath);
AssetConfig* parse_assets_config(char* source);
