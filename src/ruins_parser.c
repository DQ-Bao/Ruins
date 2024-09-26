#include "ruins_parser.h"
#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_string.h"
#include <stdio.h>
#define CHUNK_SIZE Megabytes(1)

// NOTE: this function may be inefficient with very large files
string file_read_to_string(char* filepath)
{
    string content = { 0 };

    FILE* file;
    if (fopen_s(&file, filepath, "r") != 0) { return content; }

    u64   length = 0;
    char* buffer = NULL;
    while (!feof(file))
    {
        buffer = (char*)realloc(buffer, length + CHUNK_SIZE + 1);
        if (!buffer) { return content; }

        u64 bytes_read = fread(buffer, 1, CHUNK_SIZE, file);
        if (ferror(file)) { return content; }

        length += bytes_read;

        if (bytes_read < CHUNK_SIZE)
        {
            buffer = (char*)realloc(buffer, length + 1);
            if (!buffer) { return content; }
        }
    }

    fclose(file);

    content.count = length;
    content.data  = buffer;

    content.data[content.count] = '\0';
    content.head                = content.data;
    return content;
}

DynamicArray parse_assets_config(string source)
{
    string       temp    = string_copy(source);
    DynamicArray configs = darray_create(AssetConfig);
    while (temp.count > 0)
    {
        string line = string_cut_from_delim(&temp, '\n');
        string_trim(&line);
        if (line.count == 0) { continue; }
        if (*line.data == '#') { continue; }
        AssetConfig config = { 0 };

        config.name = string_cut_from_delim(&line, ':');
        string_trim(&config.name);
        config.type = string_cut_from_delim(&line, '=');
        string_trim(&config.type);
        config.value = string_cut_from_delim(&line, '#');
        string_trim(&config.value);
        darray_push_end(AssetConfig, &configs, config);
        string_free(&line);
    }
    string_free(&temp);
    return configs;
}
