#include "Character.h"

Character::Character(Vector2 startPos, Vector2 charSize) 
    : position(startPos)
    , velocity({0.0f, 0.0f})
    , size(charSize)
    , isOnGround(false)
    , gravity(980.0f)
    , moveSpeed(150.0f)
    , maxFallSpeed(1000.0f)
{
}

void Character::Update(float deltaTime) {
    // Applica la gravità
    ApplyGravity(deltaTime);
    
    // Aggiorna posizione
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // Reset velocità orizzontale (viene impostata dai comandi di movimento)
    velocity.x = 0.0f;
}

void Character::SetNextJumpMultiplier(float jumpMultiplier){

nextJumpMultiplier = jumpMultiplier;

}

void Character::Draw() {
    // Disegno base - può essere overridden
    DrawRectangleV(position, size, BLUE);
}

void Character::MoveLeft(float deltaTime) {
    velocity.x = -moveSpeed;
}

void Character::MoveRight(float deltaTime) {
    velocity.x = moveSpeed;
}

void Character::ApplyGravity(float deltaTime) {
    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
        
        // Limita velocità di caduta
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed;
        }
    }
}

Rectangle Character::GetBounds() const {
    return Rectangle{position.x, position.y, size.x, size.y};
}

void Character::OnLandOnPlatform() {
    // Stub - verrà implementato quando integrato con world building
    isOnGround = true;
    velocity.y = 0.0f;
}

void Character::OnCollectPowerUp(int powerUpType) {
    // Stub - verrà implementato quando integrato con power-up system
}