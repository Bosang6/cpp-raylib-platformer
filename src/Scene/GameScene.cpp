#include "GameScene.h"

GameScene::GameScene() {
    GameInit();
}

void GameScene::GameInit() {
    platformsManager.GeneratePlatforms();
}

void GameScene::Update() {
    // Game scene update logic goes here

    BeginDrawing();
    ClearBackground(RAYWHITE);
    platformsManager.GeneratePlatforms();
    platformsManager.DrawPlatforms();
    platformsManager.UpdatePlatformsPosition();
    platformsManager.CheckDelete();
    EndDrawing();
}