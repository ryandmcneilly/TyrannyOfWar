#include<stdio.h>
#include "graphics.h"
#include "raylib.h"
#include "time.h"

#define WWIDTH 800
#define WHEIGHT 800

//TODO: Need to setup an asset loader (need to implement a hashmap?)
int main() {
    // Setup random see for rand()
    srand(time(NULL));

    size_t mapHeight = WHEIGHT/16;
    size_t mapWidth = WWIDTH/16;


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
    free_asset_loader(&loader);

    return 0;
}
