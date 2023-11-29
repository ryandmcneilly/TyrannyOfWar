#ifndef INPUT_H
#define INPUT_H

#include <raylib.h>
#include "map.h"
#include "player.h"

void move_selected_unit(Map* map, Player* player, int dX, int dY);
void handle_input(Map* map, Player* player);

#endif // !INPUT_H
