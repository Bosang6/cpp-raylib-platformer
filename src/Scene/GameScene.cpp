#include "GameScene.h"
bool GameScene::gameStart = false;

GameScene::GameScene() {
    GameInit();
}

void GameScene::GameInit() {
    gameStart = false;
    backgroundMusic.Init();
    platformsManager.Init();
    platformsManager.GeneratePlatforms();
    pickupManager.GeneratePickups();
    SetIsRuning(true);
    score = 0.0f;
    instructionsTimer = 5.0f;
    Vector2 pos = platformsManager.GetFirstPlatformPosition();
    pos.y -= player.GetBounds().y;
    player.SetPosition(pos);
    Platform::moveDownVelocity = 0.0f;
    Pickup::moveDownVelocity = 0.0f;
}

float GameScene::GetScore() const {
    return score;
}

void GameScene::UpdateScore(float deltaTime) {
    score += scoreIncrement * deltaTime * effects.GetScoreMultiplier();
}

void GameScene::DrawScore() {
    const char* scoreText = TextFormat("Score: %d", (int)score);
    int textWidth = MeasureText(scoreText, 30);
    
    DrawText(scoreText, Game::width - textWidth - 15, 11, 30, BLACK);
    DrawText(scoreText, Game::width - textWidth - 15, 10, 30, WHITE);
}

// Game scene update logic goes here
void GameScene::Update() {
    deltaTime = GetFrameTime();

    backgroundMusic.Play();

    BeginDrawing();
    ClearBackground(Color{89, 125, 206, 255}); // Blu medio

        GameScene::Updates();

        GameScene::HandleCollisions();

        GameScene::DrawGameObjects();

        GameScene::DrawUI();

        GameScene::CheckGameOver();

    EndDrawing();
}

bool GameScene::GetIsRunning() const {
    return isRunning;
}

void GameScene::SetIsRuning(bool b){
    isRunning = b;
}

void GameScene::Updates(){
   // Decrementa il timer delle istruzioni SEMPRE (fuori da if(isRunning))
    if(instructionsTimer > 0) {
        instructionsTimer -= deltaTime;
    }

    // Aggiorna punteggio (solo se il gioco è in corso)
    if(isRunning && gameStart) {
        UpdateScore(deltaTime);
    }

    // platforms update
    platformsManager.GeneratePlatforms();
    platformsManager.UpdatePlatformsPosition(deltaTime);
    platformsManager.CheckDelete();
        
    // effects and player update
    pickupManager.GeneratePickups();
    pickupManager.CheckDelete();
    effects.Update(deltaTime);
    player.Update(deltaTime, effects);
    ui.Update(deltaTime);
    pickupManager.Update(deltaTime, player, effects, score, ui);
}

void GameScene::HandleCollisions(){
    Rectangle playerBounds = player.GetBounds();
    // Collisione temporanea con piattaforma (per testare)
    for(auto& platform : platformsManager.GetPlatforms()){
        if (CheckCollisionRecs(playerBounds, platform->GetBounds()) && 
            player.GetVelocity().y > 0 &&
            playerBounds.y + playerBounds.height - player.GetVelocity().y * GetFrameTime() <= platform->GetBounds().y) {

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
            player.SetPosition({player.GetPosition().x, platform->position.y - playerBounds.height});
            player.SetVelocity({player.GetVelocity().x, 0});
            player.OnLandOnPlatform();

        } else if (player.GetPosition().y < platform->position.y - 50) {
            player.SetOnGround(false);
        }
    }
}

void GameScene::CheckGameOver(){
    // Controlla se il giocatore è caduto sotto lo schermo (Game Over)
    if(player.GetVelocity().y >= 1000 && player.GetBounds().y > Game::height){
        SetIsRuning(false);
        backgroundMusic.Close();
    }
}

void GameScene::DrawGameObjects(){
    // Disegna
    pickupManager.Draw();
    platformsManager.DrawPlatforms();
    player.Draw();    
}

void GameScene::DrawUI(){
    // UI
    DrawScore(); 
    if (instructionsTimer > 0) { 
        // Calcola l'alpha basato sul timer (fade negli ultimi 2 secondi)
        float alpha = instructionsTimer < 2.0f ? instructionsTimer / 2.0f : 1.0f;
        Color textColor = Fade(DARKGRAY, alpha);
            
        DrawText("Use A/D or Arrow Keys to move", 10, 60, 20, textColor);
        DrawText("Press SPACE to jump (double jump available)", 10, 85, 20, textColor);
    }
    effectsUI.Draw(effects);
    ui.Draw();
}