#include "Slow.h"
#include "raylib.h"
#include "EffectSystem.h"

Slow::Slow(Vector2 pos, float radius, float slowMultiplier, float durationSeconds)
    : Pickup(pos, radius, RED), slowMultiplier(slowMultiplier), durationSeconds(durationSeconds) {}

void Slow::Update(float dt) {
    Pickup::Update(dt); // Gestisce animazione e movimento
}

void Slow::Draw() const {
    float dx = MalusShakeX(); // Effetto shake
    Vector2 drawPos = { position.x + dx, position.y };
    
    if(textureLoaded) {
        float rDraw = radius * 2.0f;
        
        Rectangle dest = {
            drawPos.x,
            drawPos.y,
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
        
        // Triangolo di warning sopra lo sprite
        float w = rDraw * 0.35f;
        float h = rDraw * 0.35f;
        Vector2 a = { drawPos.x - w * 0.5f, drawPos.y - h * 0.25f }; 
        Vector2 b = { drawPos.x + w * 0.5f, drawPos.y - h * 0.25f }; 
        Vector2 c = { drawPos.x, drawPos.y + h * 0.55f };
        DrawTriangleLines(a, b, c, BLACK);
        
    } else {
        // Fallback
        DrawCircleV(drawPos, radius, RED);          
        DrawCircleLines((int)drawPos.x, (int)drawPos.y, radius, BLACK);

        float w = radius * 0.7f;   
        float h = radius * 0.7f;   
        Vector2 a = { drawPos.x - w * 0.5f, drawPos.y - h * 0.25f }; 
        Vector2 b = { drawPos.x + w * 0.5f, drawPos.y - h * 0.25f }; 
        Vector2 c = { drawPos.x, drawPos.y + h * 0.55f };
        DrawTriangleLines(a, b, c, BLACK);
    }
}

void Slow::OnCollect(Character&, EffectSystem& effects) {
    collected = true;
    effects.AddEffect(EffectSystem::EffectType::Slow, durationSeconds, slowMultiplier);
}

const char* Slow::GetCollectMessage() const { 
    return "SLOW"; 
}