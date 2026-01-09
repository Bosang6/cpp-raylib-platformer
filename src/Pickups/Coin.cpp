#include "Coin.h"
#include "raylib.h"
#include "cmath"

Coin::Coin(Vector2 pos, float radius, int value)
    : Pickup(pos, radius, YELLOW), value(value) {
    // Lo sprite sheet è già caricato da Pickup
    // frameIndex e frameTime sono già gestiti da Pickup
}

Coin::~Coin() {
    // La gestione della texture è già in Pickup
}

void Coin::Update(float dt) {
    Pickup::Update(dt); // Gestisce animazione e movimento
    
    angle += spinSpeed * dt;
    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }
}

float Coin::GetSpinScaleX() const {
    float spin = fabsf(cosf(angle));
    return minSpinScale + spin * (1.0f - minSpinScale);
}

void Coin::Draw() const {
    if(textureLoaded) {
        float s = BonusPulseScale(); // Effetto pulsante
        float rDraw = radius * drawScale * s;

        Rectangle dest = {
            position.x,
            position.y,
            rDraw * 2,
            rDraw * 2
        };

        Vector2 origin = {rDraw, rDraw};
        
        DrawTexturePro(
            spriteSheet,
            currentFrame,
            dest,
            origin,
            0.0f,
            tint  // Usa il colore YELLOW
        );
    } else {
        // Fallback se texture non caricata
        float scaleX = GetSpinScaleX();
        DrawEllipse(position.x, position.y, radius * scaleX, radius, GOLD);
        DrawEllipseLines(position.x, position.y, radius * scaleX, radius, ORANGE);
    }
}

void Coin::OnCollect(Character& character, EffectSystem& effects) {
    collected = true;
}