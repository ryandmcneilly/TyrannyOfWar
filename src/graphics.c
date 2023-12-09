#include "graphics.h"
#include "map.h"
#include "unit.h"
#include <raylib.h>


Texture2D* load_tile_assets(void) {
    // File paths correlate to TileType enum
    const char* tileFilePaths[] = {
        "./assets/tiles/Dirt.png",
        "./assets/tiles/Grass1.png",
        "./assets/tiles/Grass2.png",
        "./assets/tiles/Tree.png",
        "./assets/tiles/Shore.png",
        "./assets/tiles/Shore.png",
        "./assets/tiles/Shore.png",
        "./assets/tiles/Shore.png",
        "./assets/tiles/Shore.png"
    };
 
    Texture2D* tileTextures = (Texture2D*)calloc(NUM_TILES, sizeof(Texture2D));
    for (int i = 0; i < NUM_TILES; i++) {
        tileTextures[i] = LoadTexture(tileFilePaths[i]);
    }
    
    return tileTextures; 
}


Texture2D* load_building_assets(void) {
    const char* buildingFilePaths[] = {
        "./assets/buildings/CyanKeep.png",
        "./assets/buildings/RedKeep.png",
    };

    Texture2D* buildingTextures = (Texture2D*)calloc(NUM_BUILDINGS, sizeof(Texture2D));
    for (int i = 0; i < NUM_BUILDINGS; ++i) {
        buildingTextures[i] = LoadTexture(buildingFilePaths[i]);
    }

    return buildingTextures;
}


Texture2D* load_unit_assets(void) {
    const char* unitFilePaths[] = {
        "./assets/sprites/Orc-Grunt.png", 
    };

    Texture2D* unitTextures = (Texture2D*)calloc(NUM_UNITS, sizeof(Texture2D));
    for (int i = 0; i < NUM_UNITS; ++i) {
        unitTextures[i] = LoadTexture(unitFilePaths[i]);
    }

    return unitTextures;
}


AssetLoader* load_assets(void) {
    AssetLoader* loader = malloc(sizeof(AssetLoader));
    loader->tiles = load_tile_assets();
    loader->buildings = load_building_assets();
    loader->units = load_unit_assets();
    return loader; 
}


void free_asset_loader(AssetLoader* loader) {
    free(loader->buildings);
    free(loader->tiles);
}

void drawTileTexture(Map* map, AssetLoader* loader, enum TileType type, size_t row, size_t col) {
    Texture2D texture = loader->tiles[type];
    // Target pixel coords
    int posX = row * 16 * SCALE;
    int posY = col * 16 * SCALE;

    Vector2 origin = (Vector2){0, 0};
    if (type >= SAND && type <= SHORE4) {
        int offset = type - SAND; 
        Rectangle src = (Rectangle) {offset * 16, 0, (float)texture.width / 5, (float)texture.height };
        Rectangle dst = (Rectangle){posX, posY, (float)texture.width / 5 * SCALE, (float)texture.height * SCALE };
        DrawTexturePro(texture, src, dst, origin, 0, WHITE);
    } else {
        Rectangle src = (Rectangle){0, 0, texture.width, texture.height};
        Rectangle dst = (Rectangle){posX, posY, texture.width * SCALE, texture.height * SCALE};
        DrawTexturePro(texture, src, dst, origin, 0, WHITE);
    }        
}


void drawBuildingTexture(Map* map, AssetLoader* loader, enum BuildingType buildingType, size_t row, size_t col) {
    Texture2D texture = loader->buildings[buildingType];
    // Target pixel coords
    int posX = row * 16 * SCALE;
    int posY = col * 16 * SCALE;

    // 32 x 32 Texture on 3x2 grid
    Rectangle src = (Rectangle){0, 0, (float)texture.width / 3, (float)texture.height / 2}; 
    Rectangle dst = (Rectangle){posX, posY, (float)texture.width / 3 / 2 * SCALE, (float)texture.height / 2 / 2 * SCALE};
    Vector2 origin = (Vector2){0, 0};
    DrawTexturePro(texture, src, dst, origin, 0, WHITE);
}


void drawUnitTexture(Map* map, AssetLoader* loader, Unit* unit, size_t row, size_t col, bool isSelected) {
    Texture2D texture = loader->units[unit->unitType]; 
    int posX = row * 16 * SCALE;
    int posY = col * 16 * SCALE;

    size_t atlasWidth = 32;
    size_t atlasHeight = 8;
    Rectangle src = (Rectangle){0, 0, (float)32, (float)32};
    Rectangle dst = (Rectangle){posX, posY, 32 / 2.0 * SCALE, 32 / 2.0 * SCALE};
    
    Vector2 origin = (Vector2){0, 0};

    DrawTexturePro(texture, src, dst, origin, 0, isSelected ? GREEN : WHITE);
}


void drawBuildMenu(Map* map) {
    Rectangle menu = (Rectangle) {UPPERLEFTX, UPPERLEFTY, LOWERRIGHTX, LOWERRIGHTY};
    DrawRectangleRounded(menu, 0.1, 1, BEIGE);
}

void displayMenuStat(Map* map, Menu* menu) {
    char health[6];
    sprintf(health, "%.2f", menu->health);
    DrawText(health, 10, 10, 20, DARKGRAY);
}


void draw_map(Map* map, AssetLoader* loader, Player* player) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            // Draw tiles
            drawTileTexture(map, loader, map->tiles[i][j].type, i, j);
            // Draw tree
            if (map->tiles[i][j].hasTree) {
                drawTileTexture(map, loader, TREE, i, j);
            }

            if (map->tiles[i][j].tileData.hasKeep) {
                
                drawBuildingTexture(map, loader, CYAN_KEEP, i, j);
            }

            if (map->tiles[i][j].tileData.hasUnit) {
                bool isSelected = i == player->selectedUnit->col && j == player->selectedUnit->row;
                drawUnitTexture(map, loader, map->tiles[i][j].tileData.unit, i, j, isSelected);
            }
        }
    }
}

