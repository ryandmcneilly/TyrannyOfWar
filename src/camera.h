#ifndef CAMERA_H
#define CAMERA_H 

#include "raylib.h"
#include "map.h"

#define EDGE_SCROLL_SENS 0.9


Tile* cursorToTile(Map* map, Camera2D camera);
void handle_zoom(Camera2D* cam, float wheel);
void edge_scroll(Camera2D* cam);

#endif
