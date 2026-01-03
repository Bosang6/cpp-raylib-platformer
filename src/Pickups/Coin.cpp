#include "Coin.h"
#include "raylib.h"
#include "cmath"



Coin::Coin(Vector2 pos, float radius, int value)
    : Pickup(pos, radius), value(value) {}


void Coin::Update(float dt) {
    
    Pickup::Update(dt);
    
    angle += spinSpeed * dt;

    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }
}    


// Schiaccia la moneta
float Coin::GetSpinScaleX() const
{
    float spin = fabsf(cosf(angle));
    return minSpinScale + spin * (1.0f - minSpinScale);
}


void Coin::Draw() const
{
    float scaleX = GetSpinScaleX();

    // Disegno ellisse schiacciata
    DrawEllipse(position.x, position.y, radius * scaleX, radius, GOLD);
    DrawEllipseLines(position.x, position.y, radius * scaleX, radius, ORANGE);
}



void Coin::OnCollect(Character& character, EffectSystem& effects) {
    collected = true;

}


