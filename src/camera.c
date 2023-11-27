#include "camera.h"
#include "graphics.h"
#include "stdio.h"
#include <raylib.h>
#include <wchar.h>

// TODO: Figure out max and min zooms here
void handle_zoom(Camera2D* cam, float wheel) {
    // Checks if mouse wheel was actually moved
    if (wheel == 0) {
        return;
    }
    
    Vector2 mousePosition = GetMousePosition();
    // Gets world point
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, *cam);
    // Offset is where mouse is
    cam->offset = mousePosition;
    cam->target = mouseWorldPos; 
    cam->zoom += wheel * 0.125f;

}


void edge_scroll(Camera2D* cam) {
    size_t step = 1;
    Vector2 mousePosition = GetMousePosition();

    if (mousePosition.x >= WWIDTH * (1 - EDGE_SCROLL_SENS)) {
        //cam->target.x += step / cam->zoom;
        // wwidth / zoom + target.x
        cam->target.x += step / cam->zoom;
    }

    if (mousePosition.x <= WWIDTH * EDGE_SCROLL_SENS ) {
        cam->target.x -=  step / cam->zoom;

    
    } 
    if (mousePosition.y >= WHEIGHT * (1 - EDGE_SCROLL_SENS)) {
        cam->target.y += step / cam->zoom;

    } 
    if (mousePosition.y <= WHEIGHT * EDGE_SCROLL_SENS) {
        cam->target.y -= step / cam->zoom; 
    }
}


Tile* cursorToTile(Map* map, Camera2D camera) {
    Vector2 mousePosition = GetMousePosition();
    Vector2 screenToWorld = GetScreenToWorld2D(mousePosition, camera);
    if (!(0 <= screenToWorld.x && screenToWorld.x <= WWIDTH && 0 <= screenToWorld.y && screenToWorld.y <= WHEIGHT)) {
        return NULL;
    }
    return &(map->tiles[(int)screenToWorld.x / 16][(int)screenToWorld.y / 16]); // TODO: Change 16 to be dyanmic on grid size
}
