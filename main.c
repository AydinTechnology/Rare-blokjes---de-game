//bouw met: clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a main.c -o main

#include <stdlib.h>
#include "include/raylib.h"

struct gameobject {
    float posX, posY;
    unsigned char alive;
};

int main() {
    struct gameobject player = {395, 295, 0};
    struct gameobject obstaclesky = {750, 200, 0};
    struct gameobject obstacleground = {750, 300, 0};
    struct gameobject scorebord = {5, 5, 0};
    unsigned char maingameloop = 1;
    int score = 0;
    InitWindow(800, 600, "Rare blokjes");
    SetTargetFPS(60);

    while(!WindowShouldClose() && maingameloop) {
        BeginDrawing();

        ClearBackground(BLACK);

        if(player.alive) {
            DrawRectangle(player.posX, player.posY, 10, 10, GREEN);
            if(IsKeyDown(KEY_D) && player.posX < 790) player.posX += 5;
            if(IsKeyDown(KEY_A) && player.posX > 0) player.posX -= 5;
            if(IsKeyDown(KEY_SPACE) && player.posY > 0) player.posY -= 10;
            if(player.posY < 590) player.posY += 3.5;
        }

        if(obstaclesky.alive) { 
            DrawRectangle(obstaclesky.posX, 0, 50, obstaclesky.posY, GREEN);
            if(
                obstaclesky.posX < player.posX + 10 &&
                obstaclesky.posX + 50 > player.posX &&
                0 < player.posY + 10 &&
                obstaclesky.posY > player.posY
            ) {
                player.alive = 0;
                obstaclesky.alive = 0;
                obstacleground.alive = 0;
                scorebord.alive = 0;
            }
            obstaclesky.posX -= 5;
            if(obstaclesky.posX < -50) {
                obstaclesky.posX = 800; 
                obstaclesky.posY = rand() % 400;
                score++;
            }
        }

        if(obstacleground.alive) { 
            DrawRectangle(obstacleground.posX, obstacleground.posY, 50, 600 - obstacleground.posY, GREEN);
            if (
                obstacleground.posX < player.posX + 10 &&
                obstacleground.posX + 50 > player.posX &&
                obstacleground.posY < player.posY + 10 &&
                obstacleground.posY + 600 - obstacleground.posY > player.posY
            ) {
                player.alive = 0;
                obstaclesky.alive = 0;
                obstacleground.alive = 0;
                scorebord.alive = 0;
            }
            obstacleground.posX -= 5;
            if(obstacleground.posX < -50) {
                obstacleground.posX = 800; 
                obstacleground.posY = obstaclesky.posY + 125;
            }
        }

        if(scorebord.alive) DrawText(TextFormat("Score: %08i", score), scorebord.posX, scorebord.posY, 15, GREEN);

        if(!scorebord.alive) {
            DrawText(TextFormat("Rare blokjes - de game"), 250, 25, 25, GREEN);
            DrawText(TextFormat("Je laatste score was: %08i punten", score), 15, 75, 20, RED);
            DrawText(TextFormat("Druk op enter om te beginnen..."), 15, 100, 15, BLUE);
            DrawText(TextFormat("© Aydin game studio - 2024"), 610, 550, 10, GREEN);
            if(IsKeyDown(KEY_ENTER)) {
                score = 0;
                player.posX = 395; player.posY = 295; player.alive = 1;
                obstaclesky.posX = 750; obstaclesky.posY = 200; obstaclesky.alive = 1;
                obstacleground.posX = 750; obstacleground.posY = 300; obstacleground.alive = 1;
                scorebord.alive = 1;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}