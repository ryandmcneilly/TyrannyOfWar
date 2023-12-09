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
#include "state.h"


int main() {
    srand(time(NULL));
    SetTargetFPS(FPS);

    Camera2D cam = {0};
    cam.zoom = 1; // Can adjust starting zoom

    size_t mapHeight = WHEIGHT/16; //TODO: Change this 16 to be dynamic
    size_t mapWidth = WWIDTH/16;

    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");

    GameState gameState = init_game_state(1, mapHeight, mapWidth);

        
    while (!WindowShouldClose()) {
        handle_zoom(&cam, GetMouseWheelMove());
        edge_scroll(&cam);
        handle_input(gameState.map, gameState.player, &cam);

        BeginDrawing();
            ClearBackground(BLACK);
        	BeginMode2D(cam);
                draw_map(gameState.map, gameState.loader, gameState.player);
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();

    deinit_map(gameState.map);
    free_asset_loader(gameState.loader);

    return 0;
}
