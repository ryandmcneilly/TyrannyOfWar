#ifndef MAP_H
#define MAP_H

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

int get_tile_type(size_t row, size_t col);
Map inititalise_map(size_t mapHeight, size_t mapWidth);
void deinit_map(Map* map);


#endif