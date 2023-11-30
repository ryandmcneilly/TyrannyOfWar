#include <stdbool.h>
#include <stdio.h>
#include "graphics.h"
#include "map.h"
#include "raylib.h"
#include "time.h"
#include "camera.h"
#include "unit.h"
#include "player.h"
#include "input.h"


int main() {
    srand(time(NULL));
    SetTargetFPS(FPS);

    Camera2D cam = {0};
    cam.zoom = 1; // Can adjust starting zoom

    size_t mapHeight = WHEIGHT/16; //TODO: Change this 16 to be dynamic
    size_t mapWidth = WWIDTH/16;

    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");

    Map map = inititalise_map(mapHeight, mapWidth);
    AssetLoader loader = load_assets();
    Unit unit = create_unit(WARRIOR);
    Player player = {0};
    player.selectedUnit = &unit;
    place_unit(&map, &unit, 3, 5);

    while (!WindowShouldClose()) {
        handle_zoom(&cam, GetMouseWheelMove());
        edge_scroll(&cam);
        handle_input(&map, &player);

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
