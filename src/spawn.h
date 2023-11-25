#ifndef SPAWN_H
#define SPAWN_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include "map.h"


float closest_player_dist(Map* map, size_t row, size_t col);
void spawn_player(Map* map, size_t team, size_t numTeams);

#endif
