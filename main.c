#include<stdio.h>
#include "raylib.h"


int main() {
    InitWindow(500, 500, "Game name");
    while (!WindowShouldClose()) {
        BeginDrawing();
           DrawText("Hello World", 250, 250, 20, RED);
        EndDrawing();
    }
    return 0;
}



