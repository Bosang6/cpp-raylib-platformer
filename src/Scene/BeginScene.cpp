#include "BeginScene.h"
#include "Game.h"
#include "raylib.h"

void BeginScene::Update(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("JUMP!", Game::width / 2 - MeasureText("JUMP!", 50) / 2, 
    Game::height / 2 - 50 / 2, 50, DARKGRAY);
    DrawText("PRESS ENTER TO START!",  Game::width / 2 - MeasureText("PRESS ENTER TO START!", 20) / 2
    ,  Game::height / 2 + 50, 20, DARKGRAY);
    EndDrawing();
}
