#pragma once
#include "ruins_containers.h"
#include "ruins_string.h"

typedef struct
{
    string name;
    string type;
    string value;
} AssetConfig;

string       file_read_to_string(char* filepath);
DynamicArray parse_assets_config(string source);
