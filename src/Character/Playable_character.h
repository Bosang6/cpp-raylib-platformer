#pragma once
#include "Character.h"

class PlayableCharacter : public Character {
private:
    // Sistema di salto
    int jumpsRemaining;
    int maxJumps;
    float jumpForce;
    
public:
    PlayableCharacter(Vector2 startPos, Vector2 charSize);
    
    // Override metodi base
    void Update(float deltaTime) override;
    void Draw() override;
    
    // Metodi specifici del personaggio giocabile
    void Jump();
    void HandleInput(float deltaTime);
    
    // Override per gestire il reset dei salti
    void OnLandOnPlatform() override;
    
    // Getters specifici
    int GetJumpsRemaining() const { return jumpsRemaining; }
};