#include "camera.h"
#include "stdio.h"

void handle_zoom(Camera2D* cam, float wheel) {
    // Checks if mouse wheel was actually moved
    if (wheel == 0) {
        return;
    }

    // Gets world point
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *cam);
    // Offset is where mouse is
    cam->offset = GetMousePosition();
    cam->target = mouseWorldPos;
    
    // Zooom
    cam->zoom += wheel * 0.125f;
    // TODO: Figure out max and min zooms here
}
