#include "GameScene.h"

void GameScene::Update() {
    // Game scene update logic goes here

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleRounded((Rectangle){100, 100, 200, 100}, 0.2f, 10, BLACK);
    EndDrawing();
}