#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "perlin.c"

#define DIRT_CHANCE 0.3
#define LIGHT_GRASS_CHANCE 0.3
#define TREE_CHANCE 0.05
#define SCALE 1.0f
#define TREE_SCALE 1.0f

enum TileType {
    DIRT = 0,
    LIGHT_GRASS,
    DARK_GRASS,
    TREE,
    NUM_TILES,
};

typedef struct {
    bool hasKeep;
    int team;
} TileData;

typedef struct {
    enum TileType type;
    Texture2D tileTexture;
    bool hasTree;
    Texture2D treeTexture;
    TileData tileData;
} Tile;


typedef struct {
    size_t height;
    size_t width;
    Tile** tiles;
} Map;



int get_tile_type(size_t row, size_t col) {
    float noiseScale = 0.1;
    float noise = perlin(row * noiseScale, col * noiseScale); // noise in [0, 1]
    if (noise <= 0.4) { // DIRT CHANCE
        return DIRT;
    } else if (0.4 < noise && noise <= 0.55) {
        return LIGHT_GRASS;
    } else {
        return DARK_GRASS;
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
            map.tiles[i][j].type = get_tile_type(i, j);
            map.tiles[i][j].hasTree = (float)rand() / RAND_MAX < TREE_CHANCE;
            
            // Setup tile data
            TileData tileData = {0};
            tileData.hasKeep = false;
            map.tiles[i][j].tileData = tileData;
        }
    }
    
    return map;
}


void deinit_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        free(map->tiles[i]);
    }
    free(map->tiles);
}
