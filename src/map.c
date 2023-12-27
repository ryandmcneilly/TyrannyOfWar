#include "map.h"
#include "spawn.h"
#include <stdlib.h>

int get_tile_type(size_t row, size_t col, float randomNoise, float noiseScale) {
    float oceanArea = 0.3;
    float shore1cumProb = oceanArea - 0.05;
    float shore2CumProb = shore1cumProb - 0.05;
    float shore3CumProb = shore2CumProb - 0.05;
    float shore4CumProb = shore3CumProb - 0.05;
    float space_left = 1 - oceanArea;
    
    float scalar = noiseScale / (noiseScale * 0.1);
    float noise = perlin((row + randomNoise) / scalar, (col + randomNoise) / scalar);

    // TODO: Could make this cleaner 
    if (noise < shore4CumProb) { 
        return SHORE4;
    } else if (noise < shore3CumProb) {
        return SHORE3;
    } else if (noise < shore2CumProb) {
        return SHORE2;
    } else if (noise < shore1cumProb) {
        return SHORE1;
    } else if (noise < oceanArea) {
        return SAND;
    } else if (noise < space_left * 0.15 + oceanArea) {
        return DIRT;
    } else if (noise < space_left * 0.5 + oceanArea) {
        return LIGHT_GRASS;
    } else {                                   
        return DARK_GRASS;
    } 
}


bool valid_tree_tile(enum TileType type) {
    return !(SAND <= type && type <= SHORE4);
}


// Builds the map
Map* inititalise_map(size_t mapHeight, size_t mapWidth) {
    Map* map = malloc(sizeof(Map));
    map->height = mapHeight;
    map->width = mapWidth;
    srand((unsigned int)time(NULL)); 
    
    // Allocate
    map->tiles = (Tile**)calloc(mapHeight, sizeof(Tile*));
    for (size_t i = 0; i < mapHeight; ++i) {
        map->tiles[i] = (Tile*)calloc(mapWidth, sizeof(Tile));
    }

    float noiseScale = 1000.0f;
    float noise = ((float)rand() / RAND_MAX) * noiseScale;

    for (size_t i = 0; i < mapHeight; ++i) {
        for (size_t j = 0; j < mapWidth; ++j) {
            map->tiles[i][j].type = get_tile_type(i, j, noise, noiseScale);
            map->tiles[i][j].hasTree = valid_tree_tile(map->tiles[i][j].type ) 
                && (float) rand() / RAND_MAX < TREE_CHANCE;
            map->tiles[i][j].row = i;
            map->tiles[i][j].col = j;
            
            // Setup tile data
            TileData tileData = {0};
            tileData.hasKeep = false;
            map->tiles[i][j].tileData = tileData;
        }
    }
    spawn_player(map, 1, 2);
    return map;
}


void place_unit(Map* map, Unit* unit, size_t row, size_t col) {
    map->tiles[row][col].tileData.hasUnit = true;
    map->tiles[row][col].tileData.unit = unit;
    unit->row = row;
    unit->col = col;
}


bool can_unit_move(Unit* unit, Tile tile) {
    if (!unit) return false;
    int manhattenDistance = abs((int)(unit->row - tile.row)) + abs((int)(unit->col - tile.col));
    bool isOcean = SHORE1 <= tile.type && tile.type && SHORE4;
    return manhattenDistance <= unit->stats->movement && !isOcean && !tile.hasTree;
}


void deinit_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        free(map->tiles[i]);
    }
    free(map->tiles);
}
