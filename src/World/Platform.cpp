#include "Platform.h"

// Variabili statiche
Texture2D Platform::textureNormal = {0};
Texture2D Platform::textureBreakable = {0};
Texture2D Platform::textureMoving = {0};
bool Platform::texturesLoaded = false;

Platform::Platform(const Vector2& pos, E_PlatformType t)
    : GameObject(pos), bounds{pos.x, pos.y, width, height}, type{t}
{
    // Carica le texture la prima volta
    if(!texturesLoaded) {
        LoadTextures();
    }
}

void Platform::LoadTextures() {
    textureNormal = ::LoadTexture("assets/platform_normal.png");
    textureBreakable = ::LoadTexture("assets/platform_breakable.png");
    textureMoving = ::LoadTexture("assets/platform_moving.png");
    texturesLoaded = true;
}

// Le texture vengono scaricate dal PlatformsManager
void Platform::UnloadTextures() {
    if(texturesLoaded) {
        ::UnloadTexture(textureNormal);
        ::UnloadTexture(textureBreakable);
        ::UnloadTexture(textureMoving);
        texturesLoaded = false;
    }
}

void Platform::Draw() const {
    if(texturesLoaded && textureNormal.id > 0) {
        // Disegno con texture
        DrawTexturePro(
            textureNormal,
            {0, 0, (float)textureNormal.width, (float)textureNormal.height},
            bounds,
            {0, 0},
            0.0f,
            WHITE
        );
    } else {
        // Fallback
        DrawRectangleRounded(bounds, 0.2f, 10, BLACK);
        
    }
}

void Platform::UpdatePosition(float dt){
    position.y += dt * moveDownVelocity;
    bounds.y = position.y;
}

const Rectangle& Platform::GetBounds() const {
    return bounds;
}

Vector2 Platform::GetSurfaceCenter() const {
    return Vector2{position.x + width/2, position.y};
}

const E_PlatformType Platform::GetType() const{
    return type;
}