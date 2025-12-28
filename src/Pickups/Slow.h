#pragma once
#include "Pickup.h"

// Forward declaration
class Character;
class EffectSystem;

// Classe che rappresenta l'effetto di rallentamento nel gioco
class Slow : public Pickup {
    
    private:
        float slowMultiplier = 0.5f;      // Fattore di rallentamento (es. 0.5 = 50% velocità)
        float durationSeconds = 5.0f;        // Durata dell'effetto in secondi

    public:

        // Costruttore dello slow
        Slow(Vector2 pos, float radius = 10.f, float slowMultiplier = 0.5f, float duration = 5.0f);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character, EffectSystem& effects) override;

};