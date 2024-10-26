#include "ruins_parser.h"
#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_string.h"
#include <stdio.h>
#include <stdlib.h>
#define CHUNK_SIZE Megabytes(1)

// NOTE: this function may be inefficient with very large files
string_view file_read_to_string(char** buffer, char* filepath)
{
    string_view content = { 0 };

    FILE* file;
    if (fopen_s(&file, filepath, "r") != 0) { return content; }

    u64 length = 0;
    while (!feof(file))
    {
        *buffer = (char*)realloc(*buffer, length + CHUNK_SIZE + 1);
        if (!(*buffer)) { return content; }

        u64 bytes_read = fread((*buffer), 1, CHUNK_SIZE, file);
        if (ferror(file)) { return content; }

        length += bytes_read;

        if (bytes_read < CHUNK_SIZE)
        {
            *buffer = (char*)realloc((*buffer), length + 1);
            if (!(*buffer)) { return content; }
        }
    }

    fclose(file);

    (*buffer)[length] = '\0';
    content.count     = length;
    content.data      = *buffer;
    return content;
}

AssetConfig* parse_assets_config(char* source)
{
    string_view  source_view = sv_from_cstr(source);
    AssetConfig* configs     = da_create(AssetConfig);
    while (source_view.count > 0)
    {
        string_view line = sv_shift_by_delim(&source_view, '\n');
        sv_trim(&line);
        if (line.count == 0 || *line.data == '#') { continue; }
        AssetConfig config = { 0 };

        config.name = sv_shift_by_delim(&line, ':');
        sv_trim(&config.name);
        config.type = sv_shift_by_delim(&line, '=');
        sv_trim(&config.type);
        config.value = sv_shift_by_delim(&line, '#');
        sv_trim(&config.value);

        da_push(configs, config);
    }
    return configs;
}
