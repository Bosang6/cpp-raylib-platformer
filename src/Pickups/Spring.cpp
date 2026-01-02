#include "Spring.h"
#include "raylib.h"
#include "Character/Character.h"


// Costruttore dello spring
Spring::Spring(Vector2 pos, float radius, float jumpMultiplier)
    : Pickup(pos, radius), jumpMultiplier(jumpMultiplier) {}


void Spring::Update(float dt) {
    // Per ora niente anicamzioni
}


void Spring::Draw() const {
    // Disegno dello spring come un cerchio verde
    DrawCircleV(position, radius, GREEN);
    DrawCircleLines(
        (int)position.x,
        (int)position.y,
        radius,
        DARKGREEN
    );

    // Disegno di una molla stilizzata
    DrawLine((int)position.x - radius * 0.5f, (int)position.y,
             (int)position.x + radius * 0.5f, (int)position.y, DARKGREEN);

}

// Spring scope : potenzia SOLO il prossimo salto (one-shot), poi si resetta nel Character
void Spring::OnCollect(Character& character, EffectSystem& ) {

    collected = true;
    
    character.SetNextJumpMultiplier(jumpMultiplier);

    // Implementazione futura : effetto sonoro e visivo

}


