#include "Slow.h"
#include "raylib.h"
#include "EffectSystem.h"



Slow::Slow(Vector2 pos, float radius, float slowMultiplier, float durationSeconds)
    : Pickup(pos, radius), slowMultiplier(slowMultiplier), durationSeconds(durationSeconds) {}


void Slow::Update(float dt) {
    Pickup::Update(dt);
}


void Slow::Draw() const {
    
    float dx = MalusShakeX();   
    Vector2 drawPos = { position.x + dx, position.y };

    DrawCircleV(drawPos, radius, RED);          
    DrawCircleLines((int)drawPos.x, (int)drawPos.y, radius, BLACK);

    float w = radius * 0.7f;   
    float h = radius * 0.7f;   

    Vector2 a = { drawPos.x - w * 0.5f, drawPos.y - h * 0.25f }; 
    Vector2 b = { drawPos.x + w * 0.5f, drawPos.y - h * 0.25f }; 
    Vector2 c = { drawPos.x,           drawPos.y + h * 0.55f };  

    DrawTriangleLines(a, b, c, BLACK);

}


void Slow::OnCollect(Character&, EffectSystem& effects) {
    collected = true;

    effects.AddEffect(EffectSystem::EffectType::Slow, durationSeconds, slowMultiplier);

}

const char* Slow::GetCollectMessage() const { return "SLOW"; }

