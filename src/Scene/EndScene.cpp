#include "EndScene.h"
#include "Game.h"

void EndScene::Update() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("GAME OVER!", Game::width / 2 - MeasureText("GAME OVER!", 50) / 2, 
    Game::height / 2 - 50 / 2, 50, DARKGRAY);
    DrawText("PRESS ENTER TO RESTART!",  Game::width / 2 - MeasureText("PRESS ENTER TO RESTART!", 20) / 2
    ,  Game::height / 2 + 50, 20, DARKGRAY);
    EndDrawing();
}