#include "Spring.h"
#include "raylib.h"
#include "Character/Character.h"


// Costruttore dello spring
Spring::Spring(Vector2 pos, float radius, float jumpMultiplier)
    : Pickup(pos, radius), jumpMultiplier(jumpMultiplier) {}


void Spring::Update(float dt) {
    Pickup::Update(dt);
}

// Funzione helper LOCALE a questo file per disegnare la molla
static void DrawSpringIcon(Vector2 center, float radius, Color col)
{
    float pad = radius * 0.35f;
    float top = center.y - (radius - pad);
    float bottom = center.y + (radius - pad);
    float amp = radius * 0.30f;

    const int segments = 6;

    Vector2 prev = { center.x, top };

    for (int i = 1; i <= segments; ++i)
    {
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
    float r = radius * s;

    DrawCircleV(position, r, GREEN);
    DrawCircleLines((int)position.x, (int)position.y, r, DARKGREEN);

    // Icona molla interna
    DrawSpringIcon(position, r, DARKGREEN);

}

// Spring scope : potenzia SOLO il prossimo salto (one-shot), poi si resetta nel Character
void Spring::OnCollect(Character& character, EffectSystem& ) {

    collected = true;
    
    character.SetNextJumpMultiplier(jumpMultiplier);

    // Implementazione futura : effetto sonoro e visivo

}

const char* Spring::GetCollectMessage() const { return "JUMP BOOST"; }






