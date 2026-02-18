#include "ReverseControl.h"
#include "Character/Character.h"
#include "Pickups/EffectSystem.h"
#include "raylib.h"

ReverseControl::ReverseControl(Vector2 pos, float radius, float durationSeconds)
    : Pickup(pos, radius, Color{120, 0, 255, 190}), durationSeconds(durationSeconds) {}


void ReverseControl::Update(float dt) {
    Pickup::Update(dt);
}

void ReverseControl::Draw() const {
    float dx = MalusShakeX(); //Effetto shake
    Vector2 drawPos = { position.x + dx, position.y };

    if (textureLoaded) {
        float rDraw = radius * 2.0f;

        Rectangle dest = {
            drawPos.x,
            drawPos.y,
            rDraw * 2,
            rDraw * 2
        };

        Vector2 origin = { rDraw, rDraw };

        DrawTexturePro(
            spriteSheet,
            currentFrame,
            dest,
            origin,
            0.0f,
            tint  
        );

        const char* sym = "<>";
        int fontSize = (int)(rDraw * 0.55f);
        if (fontSize < 14) fontSize = 14;

        int tw = MeasureText(sym, fontSize);
        DrawText(sym,
                 (int)(drawPos.x - tw * 0.5f),
                 (int)(drawPos.y - fontSize * 0.5f),
                 fontSize,
                 BLACK);

    } else {
        // Fallback cerchio viola
        DrawCircleV(drawPos, radius, PURPLE);
        DrawCircleLines((int)drawPos.x, (int)drawPos.y, radius, BLACK);

        const char* sym = "<>";
        int fontSize = (int)(radius * 1.1f);
        if (fontSize < 12) fontSize = 12;

        int tw = MeasureText(sym, fontSize);
        DrawText(sym,
                 (int)(drawPos.x - tw * 0.5f),
                 (int)(drawPos.y - fontSize * 0.5f),
                 fontSize,
                 BLACK);
    }
}


void ReverseControl::OnCollect(Character& , EffectSystem& effects) {
    collected = true;
    effects.AddEffect(
        EffectSystem::EffectType::ReverseControl,
        durationSeconds,
        1.0f
    );
}

const char* ReverseControl::GetCollectMessage() const { 
    return "REVERSE"; 
}

const char* ReverseControl::GetCollectSound() const {
    return "reverse";
}