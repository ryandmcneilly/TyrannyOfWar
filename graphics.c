#include "map.c"
#include "raylib.h"

enum Assets {
    BLUE_KEEP_TEXTURE = 0,
    RED_KEEP_TEXTURE,
    DIRT_TEXTURE,
    LIGHT_GRASS_TEXTURE,
    DARK_GRASS_TEXTURE,
    NUM_ASSETS_TEXTURE,
};

typedef struct {
    Texture2D*  buildings;
    Texture2D** units;
    Texture2D*  tiles;    
} AssetLoader;


AssetLoader load_assets(void) {
    AssetLoader loader = {0};
    char* filePaths[] = {
        "./buildings/CyanKeep.png",
        "./buildings/RedKeep.png",
        "./assets/tiles/Dirt.png",
        "./assets/tiles/Grass1.png",
        "./assets/tiles/Grass2.png",
        "./assets/tiles/Dirt.png",
    };

    
}

void draw_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            int posX = i * 16 * SCALE;
            int posY = j * 16 * SCALE;

            // Draw tile
            Texture2D texture = map->tiles[i][j].tileTexture;
            Rectangle src = (Rectangle){0, 0, texture.width,  texture.height};
            Rectangle dest = (Rectangle){posX, posY, texture.width * SCALE, texture.height * SCALE};
            Vector2 origin = (Vector2){0, 0};
            DrawTexturePro(map->tiles[i][j].tileTexture, src, dest, origin, 0, WHITE);

            // Draw tree
            if (map->tiles[i][j].hasTree) {
                Texture2D treeTexture = map->tiles[i][j].treeTexture;
                Rectangle src = (Rectangle){0, 0, treeTexture.width, treeTexture.height};
                Rectangle dest = (Rectangle){posX, posY, treeTexture.width * SCALE, treeTexture.height * SCALE};
                Vector2 origin = (Vector2){0, 0};
                DrawTexturePro(treeTexture, src, dest, origin, 0, WHITE);
            }
        }
    }
}

