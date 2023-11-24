#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "map.h"
#include "raylib.h"

typedef struct {
    Texture2D*  buildings;
    Texture2D** units;
    Texture2D*  tiles;    
} AssetLoader;

Texture2D* load_tile_assets(void);
AssetLoader load_assets(void);
void draw_map(Map* map, AssetLoader* loader);

#endif