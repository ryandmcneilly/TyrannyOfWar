#include<stdio.h>
#include "map.c"
#include "raylib.h"

#define WWIDTH 800
#define WHEIGHT 800


int main() {
    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");
    size_t mapHeight = 30;
    size_t mapWidth = 30;
    Map map = inititalise_map(mapHeight, mapWidth);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            draw_map(&map);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
