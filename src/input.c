#include <raylib.h>
#include "camera.h"
#include "map.h"
#include "player.h"
#include "unit.h"


void move_unit(Map* map, Unit* unit, int dX, int dY) {
    // Check bounds
    if (unit->row + dX < 0 || unit->col + dY < 0) return;
    if (unit->row + dX >= map->width || unit->col + dY >= map->height) return;

    // Removes unit from tile
    map->tiles[unit->row][unit->col].tileData.hasUnit = false;
    
    // Moves the unit
    unit->row += dX;
    unit->col += dY;

    // Puts unit on new tile
    map->tiles[unit->row][unit->col].tileData.hasUnit = true;
    map->tiles[unit->row][unit->col].tileData.unit = unit;
}


void handle_input(Map* map, Player* player, Camera2D* camera) {
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return;

    // Gets tile where player clicked
    Unit* unit = player->selectedUnit;
    Tile* tileAtCursor = cursorToTile(map, *camera);
    if (tileAtCursor == NULL) return;

    // Gets difference
    int dx = tileAtCursor->row - unit->row;
    int dy = tileAtCursor->col - unit->col;
    move_unit(map, unit, dx, dy);
}
