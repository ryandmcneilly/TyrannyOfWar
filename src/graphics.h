#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "map.h"
#include "raylib.h"
#include "keep_menu.h"
#include "map.h"
#include "unit.h"
#include <raylib.h>


#define WWIDTH 800
#define WHEIGHT 800
#define FPS 144
#define MENUWIDTH 6
#define MENUHEIGHT 16

#define UPPERLEFTX 0.7 * WWIDTH * SCALE
#define UPPERLEFTY 0
#define LOWERRIGHTX WWIDTH - 0.7 * WWIDTH * SCALE
#define LOWERRIGHTY 0.7 * WHEIGHT * SCALE


// Tiles are stored based off
typedef struct {
    Texture2D*  buildings;
    Texture2D*  units;
    Texture2D*  tiles;    
} AssetLoader;


Texture2D* load_tile_assets(void);
AssetLoader* load_assets(void);

void draw_map(Map* map, AssetLoader* loader);
void free_asset_loader(AssetLoader* loader);
void drawBuildMenu(Map* map);

#endif
