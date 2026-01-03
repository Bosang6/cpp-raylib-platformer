#include "EndScene.h"
#include "Game.h"

EndScene::EndScene() : score(0.0f) {
    // Costruttore di default (se non passi il punteggio)
}

EndScene::EndScene(float finalScore) : score(finalScore) {
    // Costruttore che riceve il punteggio finale
}

void EndScene::Update() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("GAME OVER!", Game::width / 2 - MeasureText("GAME OVER!", 50) / 2, 
    Game::height / 2 - 50 / 2, 50, DARKGRAY);

     // Punteggio finale
    const char* scoreText = TextFormat("Final Score: %d", (int)score);
    DrawText(scoreText, 
        Game::width / 2 - MeasureText(scoreText, 40) / 2, 
        Game::height / 2, 
        40, 
        DARKBLUE);
        
    DrawText("PRESS ENTER TO RESTART!",  Game::width / 2 - MeasureText("PRESS ENTER TO RESTART!", 20) / 2
    ,  Game::height / 2 + 50, 20, DARKGRAY);
    EndDrawing();
}
