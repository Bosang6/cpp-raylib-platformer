#include "GameScene.h"

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
    score = 0.0f;
    instructionsTimer = 5.0f;
}

float GameScene::GetScore() const {
    return score;
}

void GameScene::UpdateScore(float deltaTime) {
    score += scoreIncrement * deltaTime;
}

void GameScene::DrawScore() {
    const char* scoreText = TextFormat("Score: %d", (int)score);
    int textWidth = MeasureText(scoreText, 30);
    
    DrawText(scoreText, Game::width - textWidth - 15, 11, 30, BLACK);
    DrawText(scoreText, Game::width - textWidth - 15, 10, 30, WHITE);
}

void GameScene::Update() {
    // Game scene update logic goes here

    BeginDrawing();
        ClearBackground(Color{135, 206, 235, 255});
        float deltaTime = GetFrameTime();

        // Decrementa il timer delle istruzioni SEMPRE (fuori da if(isRunning))
        if(instructionsTimer > 0) {
            instructionsTimer -= deltaTime;
        }

        // Aggiorna punteggio (solo se il gioco è in corso)
        if(isRunning) {
            UpdateScore(deltaTime);
        }

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

        // Controlla se il giocatore è caduto sotto lo schermo (Game Over)
        if(player.GetVelocity().y >= 1000 && playerBounds.y > Game::height){
            SetIsRuning(false);
        }

        // UI
        DrawScore(); 
        if (instructionsTimer > 0) { 
            // Calcola l'alpha basato sul timer (fade negli ultimi 2 secondi)
            float alpha = instructionsTimer < 2.0f ? instructionsTimer / 2.0f : 1.0f;
            Color textColor = Fade(DARKGRAY, alpha);
            
            DrawText("Use A/D or Arrow Keys to move", 10, 60, 20, textColor);
            DrawText("Press SPACE to jump (double jump available)", 10, 85, 20, textColor);
        }
        //---------------------------------
    EndDrawing();
}

bool GameScene::GetIsRunning() const {
    return isRunning;
}

void GameScene::SetIsRuning(bool b){
    isRunning = b;
}