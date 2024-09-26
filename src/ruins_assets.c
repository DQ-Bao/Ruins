#include "ruins_assets.h"
#include "SDL2/SDL_render.h"
#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_parser.h"
#include "ruins_render.h"
#include "ruins_string.h"

Assets assets = { 0 };

Texture asset_get_texture_by_name(string name)
{
    Texture texture = { 0 };
    for (u64 i = 0; i < assets.texture_count; i++)
    {
        if (string_equals(assets.textures[i].name, name)) { return assets.textures[i].texture; }
    }
    return texture;
}

Texture asset_get_texture_by_id(i32 id)
{
    return assets.textures[id].texture;
}

static void load_texture(SDL_Renderer* renderer, string name, string path)
{
    TextureAsset asset = { 0 };
    asset.name         = string_copy(name);
    asset.path         = string_copy(path);
    asset.texture      = texture_load_png(renderer, asset.path.data);

    assets.textures[assets.texture_count++] = asset;
}

void asset_load_from_conf(SDL_Renderer* renderer, char* filepath)
{
    string content = file_read_to_string(filepath);
    if (content.count <= 0 || !content.data) { rwarn("Can not read from file: %s", filepath); }

    DynamicArray configs = parse_assets_config(content);
    for (u64 i = 0; i < configs.count; i++)
    {
        AssetConfig config = darray_get(AssetConfig, &configs, i);
        if (string_equals_cstr(config.type, "texture")) { load_texture(renderer, config.name, config.value); }
        string_free(&config.name);
        string_free(&config.type);
        string_free(&config.value);
    }
    darray_destroy(&configs);
}
