#include "spawn.h"


// not used yet
float closest_player_dist(Map* map, size_t row, size_t col) {
    Tile** tiles = map->tiles;
    float currSmallestDist = FLT_MAX; // init as biggest float
    for (int i = 0; i < map->width; ++i) {
        for (int j = 0; j < map->height; ++j) {
            Tile tile = map->tiles[i][j];
            if (tile.tileData.hasKeep) {
                float distance = sqrt(pow(row - i, 2) + pow(col - j, 2));
                currSmallestDist = distance < currSmallestDist ? distance : currSmallestDist;
            }
        }
    }
    return currSmallestDist;
}

// TODO: Optimise random coordinates (spiral traversal?)
void spawn_player(Map* map, size_t team, size_t numTeams) {
    float minDistance = sqrt(pow(map->width, 2) + pow(map->height, 2)) / (numTeams + 1);

    while(true) {
        // Generate random cooridnates
        size_t posX = rand() % map->width;
        size_t posY = rand() % map->height;
        
        if (!(map->tiles[posX][posY].tileData.hasKeep) && closest_player_dist(map, posX, posY) > minDistance) {
            map->tiles[posX][posY].tileData.hasKeep = true; // place spawn 
            map->tiles[posX][posY].tileData.team = team; // set team
            break;
        }
    }
}
