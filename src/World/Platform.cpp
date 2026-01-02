#include "Platform.h"

void Platform::Draw() const {
    DrawRectangleRounded(bounds, 0.2f, 10, BLACK);
}

void Platform::UpdatePosition(float dt){
    position.y += dt * moveDownVelocity;
    bounds.y += dt * moveDownVelocity;
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