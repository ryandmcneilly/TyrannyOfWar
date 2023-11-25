#include "map.h"
#include "spawn.h"

int get_tile_type(size_t row, size_t col, float oceanArea) {   
    float SHORE1_NOISE = oceanArea - 0.05;
    float SHORE2_NOISE = SHORE1_NOISE - 0.05;
    float SHORE3_NOISE = SHORE2_NOISE - 0.05;
    float SHORE4_NOISE = SHORE3_NOISE - 0.05;
    float space_left = 1 - oceanArea;

    float noiseScale = 10.0f; // TODO: somehow make it random and still look nice
    float noise = perlin(row / noiseScale, col / noiseScale); // noise in [0, 1]

    if (noise < SHORE4_NOISE) { 
        return SHORE4;
    } else if (noise < SHORE3_NOISE) {
        return SHORE3;
    } else if (noise < SHORE2_NOISE) {
        return SHORE2;
    } else if (noise < SHORE1_NOISE) {
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
Map inititalise_map(size_t mapHeight, size_t mapWidth) {
    Map map = {0};
    map.height = mapHeight;
    map.width = mapWidth;
    srand((unsigned int)time(NULL)); 
    // Allocate
    map.tiles = (Tile**)calloc(mapHeight, sizeof(Tile*));
    for (size_t i = 0; i < mapHeight; ++i) {
        map.tiles[i] = (Tile*)calloc(mapWidth, sizeof(Tile));
    }
    // Fill grid

    float SAND_NOISE = (float)rand()/RAND_MAX/10 * 3 + 0.2;

    for (size_t i = 0; i < mapHeight; ++i) {
        for (size_t j = 0; j < mapWidth; ++j) {
            map.tiles[i][j].type = get_tile_type(i, j, SAND_NOISE);
            map.tiles[i][j].hasTree = valid_tree_tile(map.tiles[i][j].type ) 
                && (float) rand() / RAND_MAX < TREE_CHANCE;
            
            // Setup tile data
            TileData tileData = {0};
            tileData.hasKeep = false;
            map.tiles[i][j].tileData = tileData;
        }
    }
    spawn_player(&map, 1, 2);
    return map;
}


void place_unit(Map* map, Unit* unit, size_t row, size_t col) {
    map->tiles[row][col].tileData.hasUnit = true;
    map->tiles[row][col].tileData.unit = unit;
    unit->row = row;
    unit->col = col;
}

void deinit_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        free(map->tiles[i]);
    }
    free(map->tiles);
}
