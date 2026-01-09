#include "Pickup.h"

Texture2D Pickup::spriteSheet = {0};
bool Pickup::textureLoaded = false;
int Pickup::instanceCount = 0;
float Pickup::moveDownVelocity = 0.0f;

Pickup::Pickup(Vector2 pos, float r, Color tintColor)
    : position(pos), radius(r), tint(tintColor), frameIndex(0), frameTime(0.0f) {
    instanceCount++;
    if(!textureLoaded) LoadSpriteSheet();
    currentFrame = {0, 0, 16, 16}; // Default
}

Pickup::~Pickup() {
    instanceCount--;
    if(instanceCount == 0 && textureLoaded) UnloadSpriteSheet();
}

void Pickup::Update(float dt) {
    animTime += dt;
    position.y += dt * moveDownVelocity;
    
    if(textureLoaded) {
        frameTime += dt;
        if(frameTime >= 0.08f) {
            frameTime = 0.0f;
            frameIndex = (frameIndex + 1) % 12;
            currentFrame.x = frameIndex * 16;
        }
    }
}

float Pickup::BonusPulseScale(float speed, float amount) const {
    return 1.0f + sinf(animTime * speed) * amount;
}

float Pickup::MalusShakeX(float speed, float pixel) const {
    return sinf(animTime * speed) * pixel;
}

bool Pickup::CheckCollisionPlayer(const Rectangle& charBounds) const {
    return CheckCollisionCircleRec(position, radius, charBounds);
}

void Pickup::LoadSpriteSheet() {
    spriteSheet = ::LoadTexture("assets/coin.png");
    textureLoaded = (spriteSheet.id > 0);
}

void Pickup::UnloadSpriteSheet() {
    if(textureLoaded) ::UnloadTexture(spriteSheet);
    textureLoaded = false;
}