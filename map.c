#include <raylib.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

#define DIRT_CHANCE 0.2
#define SCALE 2.0f

enum TileType {
    DIRT = 0,
    LIGHT_GRASS,
    DARK_GRASS,
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


int get_tile_type(Map* map, size_t row, size_t col) {
    double dirtChance = DIRT_CHANCE;

    // General Case
    if (row >= 1 && col >= 1 && col < map->width - 1) {
        size_t adjDirt =    map->tiles[row-1][col-1].type == DIRT ? 1 : 0 +
                            map->tiles[row-1][col].type   == DIRT ? 1 : 0 +
                            map->tiles[row][col-1].type   == DIRT ? 1 : 0 +
                            map->tiles[row-1][col+1].type == DIRT ? 1 : 0;
        dirtChance += DIRT_CHANCE * adjDirt / 4;
    } else if (col == map->width - 1) {
        size_t adjDirt = map->tiles[row][col-1].type == DIRT ? 1 : 0;
        dirtChance += DIRT_CHANCE;
    }


    bool isDirt = ((float)rand() / RAND_MAX) <= dirtChance;
    if (isDirt) { return DIRT; }

    // Half chance of being light/dark grass tile
    return ((float)rand() / RAND_MAX) < 0.5 ? LIGHT_GRASS : DARK_GRASS;
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
            
            map.tiles[i][j].type = get_tile_type(&map, i, j);
            map.tiles[i][j].hasTree = false;
        }
    }
    
    setup_map_textures(&map);
    return map;
}


void draw_map(Map* map) { 
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            int posX = i * 16 * SCALE;
            int posY = j * 16 * SCALE;
            //printf("Placing at %d x, %d y", posX, posY);
            Rectangle src = (Rectangle){0, 0, map->tiles[i][j].tileTexture.width, map->tiles[i][j].tileTexture.width};
            Rectangle dest = (Rectangle){posX, posY, map->tiles[i][j].tileTexture.width * SCALE, map->tiles[i][j].tileTexture.height * SCALE};
            Vector2 origin = (Vector2){map->tiles[i][j].tileTexture.width * SCALE / 2, map->tiles[i][j].tileTexture.height * SCALE / 2};
            DrawTexturePro(map->tiles[i][j].tileTexture, src, dest, origin, 0, WHITE);
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
