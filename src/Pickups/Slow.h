#pragma once
#include "Pickup.h"


class Character;
class EffectSystem;

// Classe che rappresenta l'effetto di rallentamento nel gioco
class Slow : public Pickup {
    
    private:
        float slowMultiplier;           // Fattore di rallentamento (es. 0.5 = 50% velocità)
        float durationSeconds;          // Durata dell'effetto in secondi

    public:

        Slow(Vector2 pos, float radius, float slowMultiplier, float durationSeconds);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character, EffectSystem& effects) override;
        const char* GetCollectMessage() const override;
        const char* GetCollectSound() const override;

};