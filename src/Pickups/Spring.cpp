#include "Spring.h"
#include "raylib.h"
#include "../Character/Character.h"

Spring::Spring(Vector2 pos, float radius, float jumpMultiplier)
    : Pickup(pos, radius, GREEN), jumpMultiplier(jumpMultiplier) {}

void Spring::Update(float dt) {
    Pickup::Update(dt); // Gestisce animazione e movimento
}

// Funzione helper LOCALE per disegnare la molla
static void DrawSpringIcon(Vector2 center, float radius, Color col) {
    float pad = radius * 0.35f;
    float top = center.y - (radius - pad);
    float bottom = center.y + (radius - pad);
    float amp = radius * 0.30f;

    const int segments = 6;
    Vector2 prev = { center.x, top };

    for (int i = 1; i <= segments; ++i) {
        float t = (float)i / (float)segments;
        float y = top + (bottom - top) * t;
        float x = center.x + ((i % 2 == 0) ? -amp : amp);

        Vector2 cur = { x, y };
        DrawLineEx(prev, cur, 2.0f, col);
        prev = cur;
    }

    DrawLineEx(prev, { center.x, bottom }, 2.0f, col);
}

void Spring::Draw() const {
    float s = BonusPulseScale();
    
    if(textureLoaded) {
        float rDraw = radius * 2.0f * s;
        
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
        
        // Icona molla sopra lo sprite
        DrawSpringIcon(position, rDraw, DARKGREEN);
        
    } else {
        // Fallback
        float r = radius * s;
        DrawCircleV(position, r, GREEN);
        DrawCircleLines((int)position.x, (int)position.y, r, DARKGREEN);
        DrawSpringIcon(position, r, DARKGREEN);
    }
}

void Spring::OnCollect(Character& character, EffectSystem& ) {
    collected = true;
    character.SetNextJumpMultiplier(jumpMultiplier);
}

const char* Spring::GetCollectMessage() const { 
    return "JUMP BOOST"; 
}

const char* Spring::GetCollectSound() const {
    return "spring";
}