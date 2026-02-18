#include <cmath>
#include "Playable_character.h"
#include "World/Platform.h"
#include "Pickups/Pickup.h"
#include "Scene/GameScene.h"

PlayableCharacter::PlayableCharacter(Vector2 startPos, Vector2 charSize)
    : Character(startPos, charSize)
    , jumpsRemaining(2)
    , maxJumps(2)
    , jumpForce(-500.0f)
    , animationTimer(0.0f)
    , facingRight(true)
    , frameIndex(0)
    , frameTime(0.0f)
    , hasTexture(false)
{
    // Carica lo sprite sheet del cavaliere
    spriteSheet = LoadTexture("assets/knight.png");
    
    if(spriteSheet.id > 0) {
        hasTexture = true;
        // Frame size: 32x32 pixel
        currentFrame = {0, 0, 32, 32};
    }
}

PlayableCharacter::~PlayableCharacter() {
    if(hasTexture) {
        UnloadTexture(spriteSheet);
    }
}

void PlayableCharacter::Update(float deltaTime, const EffectSystem& effects) {
    // Gestisce input
    HandleInput(deltaTime, effects);
    
    // Chiama l'update base
    Character::Update(deltaTime);
    
    // Aggiorna timer per animazioni
    animationTimer += deltaTime;
    
    // Animazione dello sprite
    if(hasTexture) {
        frameTime += deltaTime;
        
        // Cambia frame ogni 0.1 secondi
        if(frameTime >= 0.1f) {
            frameTime = 0.0f;
            
            if(isOnGround) {
                // IDLE animation (riga 0, 8 frames)
                currentFrame.y = 0;
                frameIndex = (frameIndex + 1) % 8;
                currentFrame.x = frameIndex * 32;
            } else if(velocity.y < 0) {
                // JUMP animation (primi 4 frame della riga 2)
                currentFrame.y = 64; // Riga 2 (32*2)
                frameIndex = (frameIndex + 1) % 4;
                currentFrame.x = frameIndex * 32;
            } else {
                // FALL animation (ultimi 4 frame della riga 2)
                currentFrame.y = 64;
                int fallFrame = 4 + ((frameIndex + 1) % 4);
                currentFrame.x = fallFrame * 32;
            }
        }
    }

    // Wrap-around orizzontale
    if (position.x + size.x < 0) {
        position.x = GetScreenWidth();
    }
    else if (position.x > GetScreenWidth()) {
        position.x = -size.x;
    }
}

void PlayableCharacter::Draw() {
    if(hasTexture) {
        float spriteScale = std::min(size.x / 32.0f, size.y / 32.0f);
        float spriteWidth = 32.0f * spriteScale;
        float spriteHeight = 32.0f * spriteScale;
        // Disegna lo sprite
        Rectangle source = currentFrame;
        source.y -= 4;
        Rectangle dest = {
            position.x + (size.x - spriteWidth) / 2,
            position.y + size.y - spriteHeight,
            spriteWidth,
            spriteHeight
        };
        //Metodo usato per testare i bounds del personaggio con texture
        //DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, 2, RED);

        // Flip orizzontale se guarda a sinistra
        if(!facingRight) {
            source.width = -source.width;
        }
        
        DrawTexturePro(spriteSheet, source, dest, {0, 0}, 0.0f, WHITE);
        
        // Debug
        DrawText(TextFormat("Jumps: %d", jumpsRemaining), 10, 10, 20, WHITE);
        DrawText(TextFormat("Vel Y: %.2f", velocity.y), 10, 35, 20, WHITE);
               
    } else {
        // Fallback - Calcola posizione centrale per il disegno
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
        
        // Main body
        // Corpo sferico con effetto bounce
        float bodyRadius = size.x / 2;
        Color bodyColor = SKYBLUE;
        
        DrawCircleV(
            Vector2{centerX, centerY}, 
            bodyRadius, 
            bodyColor
        );
        
        // Bordo del corpo (per dare profondità)
        DrawCircleLines(centerX, centerY, bodyRadius, BLUE);
        
        // Head
        float headY = position.y + 10;
        float headRadius = 8;
        
        DrawCircleV(
            Vector2{centerX, headY}, 
            headRadius, 
            BLUE
        );
        
        // Eyes
        float eyeOffsetX = 4;
        float eyeY = headY - 1;
        
        DrawCircleV(Vector2{centerX - eyeOffsetX, eyeY}, 3.5f, WHITE);
        DrawCircleV(Vector2{centerX + eyeOffsetX, eyeY}, 3.5f, WHITE);
        
        float pupilOffsetX = facingRight ? 1.0f : -1.0f;
        DrawCircleV(Vector2{centerX - eyeOffsetX + pupilOffsetX, eyeY}, 1.5f, BLACK);
        DrawCircleV(Vector2{centerX + eyeOffsetX + pupilOffsetX, eyeY}, 1.5f, BLACK);
        
        DrawCircleV(Vector2{centerX - eyeOffsetX + 1, eyeY - 1}, 0.8f, WHITE);
        DrawCircleV(Vector2{centerX + eyeOffsetX + 1, eyeY - 1}, 0.8f, WHITE);
        
        // Mouth
        if (isOnGround) {
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
        
        // Feets
        Color footColor = BLUE;
        float footY = position.y + size.y - 2;
        
        if (!isOnGround && velocity.y < 0) {
            // Raccolti quando salta verso l'alto
            DrawCircleV(Vector2{centerX - 8, footY - 3}, 3, footColor);
            DrawCircleV(Vector2{centerX + 8, footY - 3}, 3, footColor);
        } else if (!isOnGround && velocity.y > 0) {
            // Estesi quando cade
            DrawCircleV(Vector2{centerX - 6, footY + 4}, 3, footColor);
            DrawCircleV(Vector2{centerX + 6, footY + 4}, 3, footColor);
        } else {
            // Normali quando è a terra
            float footBounce = sin(animationTimer * 10.0f) * 1.5f;
            DrawCircleV(Vector2{centerX - 7, footY + footBounce}, 3, footColor);
            DrawCircleV(Vector2{centerX + 7, footY - footBounce}, 3, footColor);
        }
        
        // Info di debug
        DrawText(TextFormat("Jumps: %d", jumpsRemaining), 10, 10, 20, WHITE);
    }
}

void PlayableCharacter::HandleInput(float deltaTime, const EffectSystem& effects) {
    
    float speed = moveSpeed * effects.GetSpeedMultiplier();
    float dir = 0.0f;
    
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dir -= 1.0f;
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dir += 1.0f;

    // Reverse Control
    if(effects.IsReverseControlActive()) dir *= -1.0f;

    velocity.x = dir * speed;

    if(dir < 0.0f) facingRight = false;
    if(dir > 0.0f) facingRight = true;

    /*
    // Movimento orizzontale
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        velocity.x = -speed;
        facingRight = false;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        velocity.x = speed;
        facingRight = true;
    }
    */
    
    // Salto
    if (IsKeyPressed(KEY_SPACE)) {
        Jump();
        if(isFirstJump){
            // Platform::moveDownVelocity = 10.0f;    // Testing
            Platform::moveDownVelocity = 100.0f;
            Pickup::moveDownVelocity = 125.0f;
            GameScene::gameStart = true;
            isFirstJump = false;
        }
    }
}

void PlayableCharacter::Jump() {
    if (jumpsRemaining > 0) {
        velocity.y = jumpForce * nextJumpMultiplier;  // applica Spring
        nextJumpMultiplier = 1.0f;                    // resetta 
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
    frameIndex = 0; 
}