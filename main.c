#include<stdio.h>
#include "raylib.h"

#define WWIDTH 1000
#define WHEIGHT 800

enum Animation {
    STANDING=0,
    WALKING_LEFT,
    WALKING_RIGHT,
    NUM_ANIMATIONS,
};

Rectangle get_texture_rectangle(enum Animation animation, Texture2D atlas) {
    Rectangle rectangle = {0};

    return rectangle;
}

int main() {
    InitWindow(WWIDTH, WHEIGHT, "Tyranny of War");

    Texture2D atlas = LoadTexture("./assets/sprites/Orc-Grunt.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);

            DrawTexture(atlas, 0, 0, WHITE);
        EndDrawing();
    }
    CloseWindow();


    return 0;
}



