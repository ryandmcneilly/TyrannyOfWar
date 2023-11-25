#include "graphics.h"
#include "map.h"

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


void drawTexture(Map* map, Texture2D texture, size_t row, size_t col) {
    // Target pixel coords
    int posX = row * 16 * SCALE;
    int posY = col * 16 * SCALE;

    Rectangle src = (Rectangle){0, 0, texture.width, texture.height};
    Rectangle dst = (Rectangle){posX, posY, texture.width * SCALE, texture.height * SCALE};
    Vector2 origin = (Vector2){0, 0};
    DrawTexturePro(texture, src, dst, origin, 0, WHITE);
}


void draw_map(Map* map, AssetLoader* loader) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            // Draw tiles
            enum TileType type = map->tiles[i][j].type;
            Texture2D tileTexture = loader->tiles[type];
            drawTexture(map, tileTexture, i, j);

            // Draw tree
            if (map->tiles[i][j].hasTree) {
                Texture2D treeTexture = loader->tiles[TREE];
                drawTexture(map, treeTexture, i, j);
            }
        }
    }
}

