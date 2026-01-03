#pragma once
#include "Character.h"
#include "Pickups/EffectSystem.h"

class PlayableCharacter : public Character {
private:
    // Sistema di salto
    int jumpsRemaining;
    int maxJumps;
    float jumpForce;

    // Animazioni e aspetto
    float animationTimer;
    float bounceOffset;
    bool facingRight;

    // Sprite sheet
    Texture2D spriteSheet;
    Rectangle currentFrame;
    int frameIndex;
    float frameTime;
    bool hasTexture;
    
public:
    PlayableCharacter(Vector2 startPos, Vector2 charSize);
     ~PlayableCharacter();
     
    // Override metodi base
    void Update(float deltaTime, const EffectSystem& effects);
    void Draw() override;
    
    // Metodi specifici del personaggio giocabile
    void Jump();
    void HandleInput(float deltaTime, const EffectSystem& effects);
    
    // Override per gestire il reset dei salti
    void OnLandOnPlatform() override;
    
    // Getters specifici
    int GetJumpsRemaining() const { return jumpsRemaining; }
};