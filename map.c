#include <raylib.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

enum TileType {
    LIGHT_GRASS = 0,
    DARK_GRASS,
    DIRT,
};

typedef struct {
    enum TileType type;
    Texture2D tileTexture;
    bool hasTree;
} Tile;

typedef struct {
    size_t height;
    size_t width;
    Tile** tiles;
} Map;




void setup_tile_texture(Tile* tile) {
    char* filepath;
    switch (tile->type) {
        case LIGHT_GRASS:
            filepath = "./assets/tiles/Grass1.png";
            break;
        case DARK_GRASS:
            filepath = "./assets/tiles/Grass2.png";
            break;
        case DIRT:
            filepath = "./assets/tiles/Dirt.png";
            break;
        default:
            return;
    }

    tile->tileTexture = LoadTexture(filepath);
}


void setup_map_textures(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            setup_tile_texture(&(map->tiles[i][j]));
        }
    }
}


// Builds the map
Map inititalise_map(size_t mapHeight, size_t mapWidth) {
    Map map = {0};
    map.height = mapHeight;
    map.width = mapWidth;

    // Allocate
    map.tiles = (Tile**)calloc(mapHeight, sizeof(Tile*));
    for (size_t i = 0; i < mapHeight; ++i) {
        map.tiles[i] = (Tile*)calloc(mapWidth, sizeof(Tile));
    }

    // Fill grid
    for (size_t i = 0; i < mapHeight; ++i) {
        for (size_t j = 0; j < mapWidth; ++j) {
            map.tiles[i][j].type = LIGHT_GRASS;
            map.tiles[i][j].hasTree = false;
        }
    }
    
    setup_map_textures(&map);
    return map;
}


void draw_map(Map* map) { 
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            int posX = i * 16;
            int posY = j * 16;
            //printf("Placing at %d x, %d y", posX, posY);
            DrawTexture((map->tiles[i][j]).tileTexture, posX, posY, WHITE);
        }
    }
}


// Frees the map
void deinit_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        free(map->tiles[i]);
    }
    free(map->tiles);
}
