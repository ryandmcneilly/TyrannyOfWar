#include<stdio.h>
#include "graphics.h"
#include "raylib.h"
#include "time.h"
#include "camera.h"

#define WWIDTH 800
#define WHEIGHT 800
#define FPS 144

int main() {
    // Setup random see for rand()
    srand(time(NULL));
    SetTargetFPS(FPS);

    Camera2D cam = {0};
    cam.zoom = 1;

    size_t mapHeight = WHEIGHT/16;
    size_t mapWidth = WWIDTH/16;


    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");

    Map map = inititalise_map(mapHeight, mapWidth);
    AssetLoader loader = load_assets();

    while (!WindowShouldClose()) {
        handle_zoom(&cam, GetMouseWheelMove());
        BeginDrawing();
            ClearBackground(BLACK);
        	BeginMode2D(cam);
                draw_map(&map, &loader);
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();

    deinit_map(&map);
    free_asset_loader(&loader);

    return 0;
}
