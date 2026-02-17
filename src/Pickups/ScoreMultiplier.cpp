#include "raylib.h"
#include "ScoreMultiplier.h"
#include "EffectSystem.h"

ScoreMultiplier::ScoreMultiplier(Vector2 pos, float radius, float scoreMultiplier, float durationSeconds)
    : Pickup(pos, radius, DARKBLUE), scoreMultiplier(scoreMultiplier), durationSeconds(durationSeconds) {}

void ScoreMultiplier::Update(float dt){
    Pickup::Update(dt); // Gestisce animazione e movimento
}

void ScoreMultiplier::Draw() const {
    if(textureLoaded) {
        float s = BonusPulseScale();
        float rDraw = radius * 2.0f * s; // Scala simile a Coin
        
        Rectangle dest = {
            position.x,
            position.y,
            rDraw * 2,
            rDraw * 2
        };
        
        Vector2 origin = {rDraw, rDraw};
        
        DrawTexturePro(
            spriteSheet,
            currentFrame,
            dest,
            origin,
            0.0f,
            tint 
        );
        
        // Testo "x2" sopra lo sprite
        const char* text = "x2";
        int fontSize = (int)(rDraw * 0.45f);
        int textWidth = MeasureText(text, fontSize);
        DrawText(text, (int)(position.x - textWidth / 2), (int)(position.y - fontSize / 2), fontSize, WHITE);
        
    } else {
        // Fallback
        float s = BonusPulseScale();
        float r = radius * s;
        const char* text = "x2";
        int fontSize = (int)(r * 0.9f);  
        int textWidth = MeasureText(text, fontSize);

        DrawCircleV(position, r, BLUE);
        DrawCircleLines((int)position.x, (int)position.y, r, DARKBLUE);
        DrawText(text, (int)(position.x - textWidth / 2), (int)(position.y - fontSize / 2), fontSize, BLACK);
    }
}

void ScoreMultiplier::OnCollect(Character&, EffectSystem& effects){
    collected = true;
    effects.AddEffect(EffectSystem::EffectType::ScoreMultiplier, durationSeconds, scoreMultiplier);
}

const char* ScoreMultiplier::GetCollectMessage() const {
    return "Score x2";
}

const char* ScoreMultiplier::GetCollectSound() const {
    return "scorex2";
}