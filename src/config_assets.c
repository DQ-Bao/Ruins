#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_parser.h"
#include "ruins_string.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        rlog(LOG_ERROR, "Can't find path to assets.conf");
        return 1;
    }

    char* content = NULL;
    file_read_to_string(&content, argv[1]);
    if (!content)
    {
        rlog(LOG_ERROR, "Failed to read file %s\n", argv[1]);
        return 1;
    }

    i32 texture_count   = 0;
    i32 sprite_count    = 0;
    i32 animation_count = 0;
    i32 tilemap_count   = 0;

    AssetConfig* configs = parse_assets_config(content);

    fprintf(stdout, "// DO NOT EDIT THIS FILE\n");
    fprintf(stdout, "// Generated by config_assets.c from %s\n", argv[1]);
    fprintf(stdout, "#pragma once\n\n");
    for (u64 i = 0; i < da_count(configs); i++)
    {
        if (sv_equals(configs[i].type, sv_from_cstr("texture")))
        {
            fprintf(stdout, "#define %s_INDEX %d\n", configs[i].name.data, texture_count);
            texture_count++;
        }
        else if (sv_equals(configs[i].type, sv_from_cstr("sprite")))
        {
            fprintf(stdout, "#define %s_INDEX %d\n", configs[i].name.data, sprite_count);
            sprite_count++;
        }
        else if (sv_equals(configs[i].type, sv_from_cstr("animation")))
        {
            fprintf(stdout, "#define %s_INDEX %d\n", configs[i].name.data, animation_count);
            animation_count++;
        }
        else if (sv_equals(configs[i].type, sv_from_cstr("tilemap")))
        {
            fprintf(stdout, "#define %s_INDEX %d\n", configs[i].name.data, tilemap_count);
            tilemap_count++;
        }
    }
    da_destroy(configs);
    free(content);

    return 0;
}
