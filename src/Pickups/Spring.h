#pragma once
#include "Pickup.h"


// Forward declaration
class Character;
class EffectManager;


// Classe che rappresenta il boost del salto nel gioco
class Spring : public Pickup {
    
    private:
        float jumpMultiplier = 1.8f;        // Moltiplicatore del boost di salto

    public:

        // Costruttore dello spring
        Spring(Vector2 pos, float radius = 10.f, float jumpMultiplier = 1.8f);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character, EffectManager& effects) override;

};
