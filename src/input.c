#include <raylib.h>
#include "map.h"
#include "player.h"

void move_selected_unit(Map* map, Player* player, int dX, int dY) {
    // Current players selected unit
    Unit* unit = player->selectedUnit;
    
    printf("%d v %d\n", player->selectedUnit->row + dX , map->width );
    // Check bounds
    if (player->selectedUnit->row + dX < 0 || player->selectedUnit->col + dY < 0) return;
    if (player->selectedUnit->row + dX >= map->width || player->selectedUnit->col + dY >= map->height) return;

    
    
    // Removes unit from tile
    map->tiles[player->selectedUnit->row][player->selectedUnit->col].tileData.hasUnit = false;
    
    printf("Old %d, %d\n", player->selectedUnit->row, player->selectedUnit->col);

    // Moves the unit
    player->selectedUnit->row += dX;
    player->selectedUnit->col += dY;

    printf("New %d, %d\n", player->selectedUnit->row, player->selectedUnit->col);
    // Puts unit on new tile
    map->tiles[player->selectedUnit->row][player->selectedUnit->col].tileData.hasUnit = true;
    map->tiles[player->selectedUnit->row][player->selectedUnit->col].tileData.unit = unit;
}

void handle_input(Map* map, Player* player) {
    if (IsKeyDown(KEY_LEFT)) move_selected_unit(map, player, -1, 0);
    if (IsKeyDown(KEY_RIGHT)) move_selected_unit(map, player, 1, 0);
    if (IsKeyDown(KEY_DOWN)) move_selected_unit(map, player, 0, 1);
    if (IsKeyDown(KEY_UP)) move_selected_unit(map, player, 0, -1);
}

