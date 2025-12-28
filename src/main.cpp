#include "raylib.h"
#include "Character/Playable_character.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Platform 2D - Character Test");
    SetTargetFPS(60);

    // Crea il personaggio giocabile
    PlayableCharacter player({400, 200}, {30, 50});
    
    // Piattaforma temporanea per testare l'atterraggio
    Rectangle testPlatform = {300, 350, 200, 20};

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        
        // Update
        player.Update(deltaTime);
        
        // Collisione temporanea con piattaforma (per testare)
        Rectangle playerBounds = player.GetBounds();
        if (CheckCollisionRecs(playerBounds, testPlatform) && 
            player.GetVelocity().y > 0) {
            player.SetOnGround(true);
            player.SetPosition({player.GetPosition().x, testPlatform.y - 50});
            player.SetVelocity({player.GetVelocity().x, 0});
            player.OnLandOnPlatform();
        } else if (player.GetPosition().y < testPlatform.y - 50) {
            player.SetOnGround(false);
        }
        
        // Draw
        BeginDrawing();
            ClearBackground(Color{135, 206, 235, 255}); // Cielo azzurro
            
            // Disegna piattaforma di test
            DrawRectangleRec(testPlatform, DARKGREEN);
            DrawRectangleLinesEx(testPlatform, 2, GREEN);
            
            // Disegna il personaggio
            player.Draw();
            
            // UI
            DrawText("Use A/D or Arrow Keys to move", 10, 60, 20, DARKGRAY);
            DrawText("Press SPACE to jump (double jump available)", 10, 85, 20, DARKGRAY);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}