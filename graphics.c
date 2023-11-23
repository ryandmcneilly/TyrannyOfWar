#include "map.c"
#include "raylib.h"


typedef struct {
    Texture2D*  buildings;
    Texture2D** units;
    Texture2D*  tiles;    
} AssetLoader;



Texture2D* load_tile_assets(void) {
    // File paths correlate to TileType enum
    const char* tileFilePaths[] = {
        "./assets/tiles/Dirt.png",
        "./assets/tiles/Grass1.png",
        "./assets/tiles/Grass2.png",
        "./assets/tiles/Tree.png",
    };
 
    Texture2D* tileTextures = (Texture2D*)calloc(NUM_TILES, sizeof(Texture2D));
    for (int i = 0; i < NUM_TILES; ++i) {
        tileTextures[i] = LoadTexture(tileFilePaths[i]);
    }
    
    return tileTextures; 
}


AssetLoader load_assets(void) {
    AssetLoader loader = {0};
    loader.tiles = load_tile_assets();
    return loader; 
}


void draw_map(Map* map, AssetLoader* loader) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            int posX = i * 16 * SCALE;
            int posY = j * 16 * SCALE;

            // Draw tile
            Tile currentTile = map->tiles[i][j];
            Texture2D texture = (loader->tiles)[currentTile.type];
            //Texture2D texture = currentTile.tileTexture;
            Rectangle src = (Rectangle){0, 0, texture.width,  texture.height};
            Rectangle dest = (Rectangle){posX, posY, texture.width * SCALE, texture.height * SCALE};
            Vector2 origin = (Vector2){0, 0};
            DrawTexturePro(texture, src, dest, origin, 0, WHITE);

            // Draw tree
            if (map->tiles[i][j].hasTree) {
                Texture2D treeTexture = (loader->tiles)[TREE];
                Rectangle src = (Rectangle){0, 0, treeTexture.width, treeTexture.height};
                Rectangle dest = (Rectangle){posX, posY, treeTexture.width * SCALE, treeTexture.height * SCALE};
                Vector2 origin = (Vector2){0, 0};
                DrawTexturePro(treeTexture, src, dest, origin, 0, WHITE);
            }
        }
    }
}

