#include "GameScene.h"
#include <iostream>

GameScene::GameScene() {
    GameInit();

    // -----effects init-------
    pickupManager.Spawn(PickupManager::Type::Coin, {300, 80});
    pickupManager.Spawn(PickupManager::Type::Slow, {200, 80});
    pickupManager.Spawn(PickupManager::Type::ScoreMultiplier, {100, 80});
    pickupManager.Spawn(PickupManager::Type::Spring, {50, 80});
    // ------------------------
}

void GameScene::GameInit() {
    platformsManager.GeneratePlatforms();
    SetIsRuning(true);
}

void GameScene::Update() {
    // Game scene update logic goes here

    BeginDrawing();
        ClearBackground(Color{135, 206, 235, 255});
        float deltaTime = GetFrameTime();

        // platforms update
        platformsManager.GeneratePlatforms();
        platformsManager.UpdatePlatformsPosition(deltaTime);
        platformsManager.CheckDelete();
        
        // effects and player update
        effects.Update(deltaTime);
        player.Update(deltaTime, effects);
        pickupManager.Update(deltaTime, player, effects);

        Rectangle playerBounds = player.GetBounds();
        // Collisione temporanea con piattaforma (per testare)
        for(auto& platform : platformsManager.GetPlatforms()){
            if (CheckCollisionRecs(playerBounds, platform->GetBounds()) && 
                playerBounds.y + playerBounds.height < platform->GetBounds().y + platform->GetBounds().height &&
                player.GetVelocity().y > 0) {

                // skip the collision handling when the platform is broken
                auto* bp = dynamic_cast<BreakablePlatform*>(platform.get());
                if(bp){
                    if(bp->IsBroken()) continue;
                }

                // start breaking timer
                if(platform->GetType() == E_PlatformType::Breakable){
                    if(auto* bp = dynamic_cast<BreakablePlatform*>(platform.get())){
                        bp->TriggerBreak();
                    }
                }

                player.SetOnGround(true);
                player.SetPosition({player.GetPosition().x, platform->position.y - 50});
                player.SetVelocity({player.GetVelocity().x, 0});
                player.OnLandOnPlatform();

            } else if (player.GetPosition().y < platform->position.y - 50) {
                player.SetOnGround(false);
            }
        }

        // Disegna
        platformsManager.DrawPlatforms();
        player.Draw();
        pickupManager.Draw();

        if(player.GetVelocity().y >= 1000 && playerBounds.y > Game::height){
            SetIsRuning(false);
        }

        // UI
        DrawText("Use A/D or Arrow Keys to move", 10, 60, 20, DARKGRAY);
        DrawText("Press SPACE to jump (double jump available)", 10, 85, 20, DARKGRAY);
        //---------------------------------
    EndDrawing();
}

bool GameScene::GetIsRunning() const {
    return isRunning;
}

void GameScene::SetIsRuning(bool b){
    isRunning = b;
}