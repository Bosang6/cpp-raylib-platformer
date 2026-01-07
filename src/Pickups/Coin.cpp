#include "Coin.h"
#include "raylib.h"
#include "cmath"


// Variabili statiche
Texture2D Coin::spriteSheet = {0};
bool Coin::textureLoaded = false;
int Coin::instanceCount = 0;


Coin::Coin(Vector2 pos, float radius, int value)
    : Pickup(pos, radius), value(value), frameIndex(0), frameTime(0.0f) {
        instanceCount++;
        // Carica la texture solo una volta
        if(!textureLoaded) {
        LoadSpriteSheet();
        }
    
        // Imposta il primo frame (12 frame orizzontali, 16x16 pixel ciascuno)
        currentFrame = {0, 0, 16, 16};
}


Coin::~Coin() {
    instanceCount--;
    
    // Scarica la texture solo quando non ci sono più monete
    if(instanceCount == 0 && textureLoaded) {
        UnloadSpriteSheet();
    }
}


void Coin::LoadSpriteSheet() {
    spriteSheet = ::LoadTexture("assets/coin.png");
    if(spriteSheet.id > 0) {
        textureLoaded = true;
    }
}


void Coin::UnloadSpriteSheet() {
    if(textureLoaded) {
        ::UnloadTexture(spriteSheet);
        textureLoaded = false;
    }
}


void Coin::Update(float dt) {
    
    Pickup::Update(dt);
    
    angle += spinSpeed * dt;

    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }

    if(textureLoaded) {
        frameTime += dt;
        
        // Cambia frame ogni 0.08 secondi
        if(frameTime >= 0.08f) {
            frameTime = 0.0f;
            frameIndex = (frameIndex + 1) % 12; // 12 frame totali
            currentFrame.x = frameIndex * 16; // Ogni frame è 16px
        }
    }

}    


// "Schiaccia" la moneta
float Coin::GetSpinScaleX() const
{
    float spin = fabsf(cosf(angle));
    return minSpinScale + spin * (1.0f - minSpinScale);
}


void Coin::Draw() const {
     if(textureLoaded) {

        float rDraw = radius * drawScale;

        // Disegna Sprite animato
        Rectangle dest = {
            position.x - radius,
            position.y - radius,
            rDraw * 2,
            rDraw * 2
        };

        Vector2 origin = {dest.width * 0.5f , dest.height * 0.5f};
        
        DrawTexturePro(
            spriteSheet,
            currentFrame,
            dest,
            origin,
            0.0f,
            WHITE
        );
    } else {
    float scaleX = GetSpinScaleX();

    // Disegno ellisse schiacciata
    DrawEllipse(position.x, position.y, radius * scaleX, radius, GOLD);
    DrawEllipseLines(position.x, position.y, radius * scaleX, radius, ORANGE);

    // debug
    // DrawCircleLines((int)position.x,(int)position.y, radius, RED);

    }    
}

void Coin::OnCollect(Character& character, EffectSystem& effects) {
    collected = true;

}