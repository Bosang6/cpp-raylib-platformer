#pragma once
#include "Pickup.h"

class Coin : public Pickup {
    
private:
    // Rotazione 
    float angle{0.0f};              
    float spinSpeed{4.0f};          
    float minSpinScale{0.2f};
    
    // Valore
    int value;                  
    
    // Per il draw
    float drawScale{2.0f};

public:
    Coin(Vector2 pos, float radius, int value);
    ~Coin();

    void Update(float dt) override;
    void Draw() const override;
    void OnCollect(Character& character, EffectSystem& effects) override;
    
    int GetValue() const {return value;}

private:
    float GetSpinScaleX() const;
};