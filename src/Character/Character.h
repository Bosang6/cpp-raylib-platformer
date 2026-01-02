#pragma once
#include "raylib.h"

class Character {
protected:
    // Posizione e fisica
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    
    // Stato
    bool isOnGround;
    
    // Costanti fisiche (possono essere modificate dalle classi derivate)
    float gravity;
    float moveSpeed;
    float maxFallSpeed;
    float nextJumpMultiplier = 1.0f;
   
public:
    Character(Vector2 startPos, Vector2 charSize);
    virtual ~Character() = default;
    
    // Metodi virtuali per permettere override
    virtual void Update(float deltaTime);
    virtual void Draw();
    
    // Movimento base
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void ApplyGravity(float deltaTime);
    
    // Interfaccia con il mondo esterno (break per ora)
    virtual void OnLandOnPlatform();
    virtual void OnCollectPowerUp(int powerUpType);
    virtual void SetNextJumpMultiplier(float jumpMultiplier);

    
    // Getters
    Vector2 GetPosition() const { return position; }
    Vector2 GetVelocity() const { return velocity; }
    Rectangle GetBounds() const;
    bool IsOnGround() const { return isOnGround; }
    
    // Setters (per il world building)
    void SetPosition(Vector2 newPos) { position = newPos; }
    void SetVelocity(Vector2 newVel) { velocity = newVel; }
    void SetOnGround(bool grounded) { isOnGround = grounded; }
};