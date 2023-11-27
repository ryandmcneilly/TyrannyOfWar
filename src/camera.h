#ifndef CAMERA_H
#define CAMERA_H 

#include "raylib.h"
#include "map.h"


Tile cursorToTile(Map* map, Camera2D camera);
void handle_zoom(Camera2D* cam, float wheel);

#endif
