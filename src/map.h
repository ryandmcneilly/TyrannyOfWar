#ifndef MAP_H
#define MAP_H

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perlin.h"
#include "unit.h"
#include "time.h"

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
    SAND,
    SHORE1,
    SHORE2,
    SHORE3,
    SHORE4,
    NUM_TILES,
};

enum BuildingType {
    CYAN_KEEP = 0,
    RED_KEEP,
    NUM_BUILDINGS,
};

typedef struct {
    bool hasKeep;
    bool hasUnit;
    Unit* unit;
    int team;
} TileData;

typedef struct {
    enum TileType type;
    bool hasTree;
    TileData tileData;
} Tile;

typedef struct {
    size_t height;
    size_t width;
    Tile** tiles;
} Map;


int get_tile_type(size_t row, size_t col, float oceanArea);
Map inititalise_map(size_t mapHeight, size_t mapWidth);
void deinit_map(Map* map);
void place_unit(Map* map, Unit* unit, size_t row, size_t col);


#endif
