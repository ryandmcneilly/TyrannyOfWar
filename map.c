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
};

typedef struct {
    enum TileType type;
    Texture2D tileTexture;
    bool hasTree;
    Texture2D treeTexture;
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

    if (tile->hasTree) {
        char* treeFilePath = "./assets/tiles/Tree.png";
        tile->treeTexture = LoadTexture(treeFilePath);
    }
}


void setup_map_textures(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        for (size_t j = 0; j < map->width; ++j) {
            setup_tile_texture(&(map->tiles[i][j]));
        }
    }
}


int get_tile_type(Map* map, size_t row, size_t col) {
    float noiseScale = 0.1;
    float noise = perlin(row * noiseScale, col * noiseScale); // noise in [0, 1]
    printf("perlin(%f, %f) = %f", row*noiseScale, col*noiseScale, noise);
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
            map.tiles[i][j].type = get_tile_type(&map, i, j);
            map.tiles[i][j].hasTree = (float)rand() / RAND_MAX < TREE_CHANCE;
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


void deinit_map(Map* map) {
    for (size_t i = 0; i < map->height; ++i) {
        free(map->tiles[i]);
    }
    free(map->tiles);
}
