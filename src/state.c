#include "state.h"


Player* init_player() {
    Player* player = malloc(sizeof(Player));
    return player;
}

GameState init_game_state(size_t numPlayers, size_t mapHeight, size_t mapWidth) {
    GameState state = {0};

    state.map = inititalise_map(mapHeight, mapWidth);
    state.loader = load_assets();
    state.player = init_player();

    return state; 
}
