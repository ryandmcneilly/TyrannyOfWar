#include<stdio.h>
#include "graphics.h"
#include "raylib.h"

#define WWIDTH 800
#define WHEIGHT 800

//TODO: Need to setup an asset loader (need to implement a hashmap?)

int main() {

    size_t mapHeight = WHEIGHT/16;
    size_t mapWidth = WWIDTH/16;

    // Load assets

    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");

    Map map = inititalise_map(mapHeight, mapWidth);
    AssetLoader loader = load_assets();
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            draw_map(&map, &loader);
        EndDrawing();
    }
    CloseWindow();

    deinit_map(&map);

    return 0;
}
