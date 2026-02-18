#pragma once
#include "Pickup.h"

class Character;
class EffectSystem;

// Classe che rappresenta l'effetto di inversione dei controlli
class ReverseControl : public Pickup {

private:
    float durationSeconds;

public:
    ReverseControl(Vector2 pos, float radius, float durationSeconds);

    void Update(float dt) override;
    void Draw() const override;
    void OnCollect(Character&, EffectSystem& effects) override;

    const char* GetCollectMessage() const override;
    const char* GetCollectSound() const override;
};
