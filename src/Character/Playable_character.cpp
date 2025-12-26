#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(Vector2 startPos, Vector2 charSize)
    : Character(startPos, charSize)
    , jumpsRemaining(2)
    , maxJumps(2)
    , jumpForce(-500.0f)
{
}

void PlayableCharacter::Update(float deltaTime) {
    // Gestisce input
    HandleInput(deltaTime);
    
    // Chiama l'update base
    Character::Update(deltaTime);
}

void PlayableCharacter::Draw() {
    // Disegno personalizzato per il giocatore
    DrawRectangleV(position, size, GREEN);
    
    // Indicatore salti rimanenti (opzionale, per debug)
    DrawText(TextFormat("Jumps: %d", jumpsRemaining), 10, 10, 20, WHITE);
}

void PlayableCharacter::HandleInput(float deltaTime) {
    // Movimento orizzontale
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        MoveLeft(deltaTime);
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        MoveRight(deltaTime);
    }
    
    // Salto
    if (IsKeyPressed(KEY_SPACE)) {
        Jump();
    }
}

void PlayableCharacter::Jump() {
    if (jumpsRemaining > 0) {
        velocity.y = jumpForce;
        jumpsRemaining--;
        isOnGround = false;
    }
}

void PlayableCharacter::OnLandOnPlatform() {
    // Chiama il metodo base
    Character::OnLandOnPlatform();
    
    // Reset dei salti
    jumpsRemaining = maxJumps;
}