#ifndef STATE_H
#define STATE_H

#include "map.h"
#include "graphics.h"
#include "player.h"
#include "graphics.h"
#include "map.h"
#include "stdlib.h"

typedef struct {
    Map* map;
    Player* player;
    size_t numPlayers;
    AssetLoader* loader;
} GameState;



GameState init_game_state(size_t numPlayers, size_t mapHeight, size_t mapWidth);


#endif
