#pragma once
#include "Pickup.h"

// Forward declaration
class Character;
class EffectSystem;

// Classe che rappresenta l'effetto di rallentamento nel gioco
class Slow : public Pickup {
    
    private:
        float slowMultiplier;      // Fattore di rallentamento (es. 0.5 = 50% velocità)
        float durationSeconds;        // Durata dell'effetto in secondi

    public:

        // Costruttore dello slow
        Slow(Vector2 pos, float radius = 10.0f, float slowMultiplier = 0.5f, float durationSeconds = 5.0f);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character, EffectSystem& effects) override;

};