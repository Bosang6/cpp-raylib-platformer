#include "raylib.h"
#include "Character.h"
#include "Playable_character.h"

int main()
{
    InitWindow(800, 450, "Hello raylib");
    SetTargetFPS(60);

    // Crea il personaggio giocabile
    PlayableCharacter player({400, 200}, {30, 50});

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        
        // Update
        player.Update(deltaTime);
        
        // TODO: logica di collisione con piattaforme
        // Es: if (CheckCollisionPlatforms(player.GetBounds())) {
        //         player.OnLandOnPlatform();
        //     }
        
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            player.Draw();
            
            DrawText("Use A/D or Arrow Keys to move, SPACE to jump", 10, 40, 20, DARKGRAY);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}