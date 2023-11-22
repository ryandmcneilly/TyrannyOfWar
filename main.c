#include<stdio.h>
#include "map.c"
#include "raylib.h"

#define WWIDTH 800
#define WHEIGHT 800

//TODO: Need to setup an asset loader (need to implement a hashmap?)


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
    deinit_map(&map);

    return 0;
}
