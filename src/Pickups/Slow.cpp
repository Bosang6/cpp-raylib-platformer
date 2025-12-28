#include "Slow.h"
#include "raylib.h"
#include "EffectSystem.h"


// Costruttore dello slow
Slow::Slow(Vector2 pos, float radius, float slowMultiplier, float duration)
    : Pickup(pos, radius), slowMultiplier(slowMultiplier), durationSeconds(duration) {}



void Slow::Update(float dt) {
    // Per ora niente animazioni, aggiunta in futuro
}

// Disegna lo slow pickup
void Slow::Draw() const {
    // Disegno dello slow come un cerchio blu
    DrawCircleV(position, radius, BLUE);
    DrawCircleLines(
        (int)position.x,
        (int)position.y,
        radius,
        DARKBLUE
    );

    // Disegno di una freccia verso il basso per indicare il rallentamento
    DrawTriangle(
        { position.x - radius * 0.5f, position.y - radius * 0.2f },
        { position.x + radius * 0.5f, position.y - radius * 0.2f },
        { position.x, position.y + radius * 0.5f },
        DARKBLUE
    );
}


// Cosa succede quando viene raccolto
void Slow::OnCollect(Character&, EffectSystem& effects) {
    collected = true;

    // Aggiunge l'effetto di rallentamento al EffectSystem
    effects.AddEffect(EffectType::Slow, durationSeconds, slowMultiplier);

    // Implementazione futura : effetto sonoro e visivo
}
