#include<stdio.h>
#include "raylib.h"

#define WWIDTH 1000
#define WHEIGHT 800

int main() {
    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");
    while (!WindowShouldClose()) {
        BeginDrawing();
           DrawText("hello", WWIDTH / 2, WHEIGHT / 2, 20, RED);
        EndDrawing();
    }
    CloseWindow();


    return 0;
}



