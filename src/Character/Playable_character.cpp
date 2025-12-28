#include <cmath>
#include "Playable_character.h"

PlayableCharacter::PlayableCharacter(Vector2 startPos, Vector2 charSize)
    : Character(startPos, charSize)
    , jumpsRemaining(2)
    , maxJumps(2)
    , jumpForce(-500.0f)
    , animationTimer(0.0f)
    , bounceOffset(0.0f)
    , facingRight(true)
{
}

void PlayableCharacter::Update(float deltaTime) {
    // Gestisce input
    HandleInput(deltaTime);
    
    // Chiama l'update base
    Character::Update(deltaTime);
    
    // Aggiorna timer per animazioni
    animationTimer += deltaTime;
    
    // Effetto "bounce" quando è a terra
    if (isOnGround) {
        bounceOffset = sin(animationTimer * 8.0f) * 2.0f;
    } else {
        bounceOffset = 0.0f;
    }
    
    /* Wrap-around orizzontale
    if (position.x + size.x < 0) {
        position.x = 800; || or GetScreenWidth()
    }
    else if (position.x > 800) {
        position.x = -size.x;
    }
    */
}

void PlayableCharacter::Draw() {
    // Calcola posizione centrale per il disegno
    float centerX = position.x + size.x / 2;
    float centerY = position.y + size.y / 2;
    
    // Ombra (solo quando è vicino a terra)
    if (isOnGround || velocity.y > -100) {
        float shadowAlpha = isOnGround ? 0.4f : 0.2f;
        DrawEllipse(
            centerX, 
            position.y + size.y + 3, 
            size.x / 2 + 2, 
            4, 
            Fade(BLACK, shadowAlpha)
        );
    }
    
    // === CORPO PRINCIPALE ===
    // Corpo sferico con effetto bounce
    float bodyRadius = size.x / 2;
    Color bodyColor = SKYBLUE;
    
    DrawCircleV(
        Vector2{centerX, centerY - bounceOffset}, 
        bodyRadius, 
        bodyColor
    );
    
    // Bordo del corpo (per dare profondità)
    DrawCircleLines(centerX, centerY - bounceOffset, bodyRadius, BLUE);
    
    // === TESTA ===
    float headY = position.y + 10 - bounceOffset;
    float headRadius = 8;
    
    DrawCircleV(
        Vector2{centerX, headY}, 
        headRadius, 
        BLUE
    );
    
    // === OCCHI ===
    float eyeOffsetX = 4;
    float eyeY = headY - 1;
    
    // Occhi bianchi
    DrawCircleV(Vector2{centerX - eyeOffsetX, eyeY}, 3.5f, WHITE);
    DrawCircleV(Vector2{centerX + eyeOffsetX, eyeY}, 3.5f, WHITE);
    
    // Pupille (si muovono leggermente in base alla direzione)
    float pupilOffsetX = facingRight ? 1.0f : -1.0f;
    DrawCircleV(Vector2{centerX - eyeOffsetX + pupilOffsetX, eyeY}, 1.5f, BLACK);
    DrawCircleV(Vector2{centerX + eyeOffsetX + pupilOffsetX, eyeY}, 1.5f, BLACK);
    
    // Riflesso negli occhi (per renderli più vivi)
    DrawCircleV(Vector2{centerX - eyeOffsetX + 1, eyeY - 1}, 0.8f, WHITE);
    DrawCircleV(Vector2{centerX + eyeOffsetX + 1, eyeY - 1}, 0.8f, WHITE);
    
    // === BOCCA ===
    if (isOnGround) {
        // Sorriso quando è a terra
        DrawCircleSector(
            Vector2{centerX, headY + 3},
            3, 
            0, 
            180, 
            8, 
            DARKBLUE
        );
    } else if (velocity.y < 0) {
        // Bocca aperta quando salta verso l'alto
        DrawCircleV(Vector2{centerX, headY + 4}, 2, DARKBLUE);
    } else {
        // Bocca sorpresa quando cade
        DrawEllipse(centerX, headY + 4, 2, 3, DARKBLUE);
    }
    
    // === PIEDINI ===
    Color footColor = BLUE;
    float footY = position.y + size.y - 2;
    
    if (!isOnGround && velocity.y < 0) {
        // Piedini raccolti quando salta verso l'alto
        DrawCircleV(Vector2{centerX - 8, footY - 3}, 3, footColor);
        DrawCircleV(Vector2{centerX + 8, footY - 3}, 3, footColor);
    } else if (!isOnGround && velocity.y > 0) {
        // Piedini estesi quando cade
        DrawCircleV(Vector2{centerX - 6, footY + 4}, 3, footColor);
        DrawCircleV(Vector2{centerX + 6, footY + 4}, 3, footColor);
    } else {
        // Piedini normali quando è a terra
        float footBounce = sin(animationTimer * 10.0f) * 1.5f;
        DrawCircleV(Vector2{centerX - 7, footY + footBounce}, 3, footColor);
        DrawCircleV(Vector2{centerX + 7, footY - footBounce}, 3, footColor);
    }
    
    // === DEBUG INFO (opzionale) ===
    DrawText(TextFormat("Jumps: %d", jumpsRemaining), 10, 10, 20, WHITE);
    DrawText(TextFormat("Vel Y: %.0f", velocity.y), 10, 35, 20, WHITE);
}

void PlayableCharacter::HandleInput(float deltaTime) {
    // Movimento orizzontale
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        MoveLeft(deltaTime);
        facingRight = false;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        MoveRight(deltaTime);
        facingRight = true;
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
    
    // Reset timer per bounce effect
    animationTimer = 0.0f;
}