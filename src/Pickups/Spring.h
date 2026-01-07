#pragma once
#include "Pickup.h"


class Character;
class EffectSystem;

// Classe che rappresenta il boost del salto nel gioco
class Spring : public Pickup {
    
    private:
        float jumpMultiplier;       

    public:

        Spring(Vector2 pos, float radius, float jumpMultiplier);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character, EffectSystem& effects) override;
        const char* GetCollectMessage() const override;


};
