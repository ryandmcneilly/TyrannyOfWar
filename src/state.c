#include "state.h"
#include "unit.h"


Player* init_player() {
    Player* player = malloc(sizeof(Player));


    
    return player;
}

GameState init_game_state(size_t numPlayers, size_t mapHeight, size_t mapWidth) {
    GameState state = {0};

    state.map = inititalise_map(mapHeight, mapWidth);
    state.loader = load_assets();
    state.player = init_player();

    Unit* unit = create_unit(WARRIOR);
    unit->row = 3;
    unit->col = 3;

    state.map->tiles[unit->row][unit->col].tileData.unit = unit;
    state.map->tiles[unit->row][unit->col].tileData.hasUnit = true;

    return state; 
}
