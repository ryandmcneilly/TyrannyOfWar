#include<stdio.h>
#include "map.c"
#include "raylib.h"

#define WWIDTH 1000
#define WHEIGHT 800


int main() {
    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");
    size_t mapHeight = 20;
    size_t mapWidth = 40;
    Map map = inititalise_map(mapHeight, mapWidth);
    draw_map(&map);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            draw_map(&map);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
