#include "MovingPlatform.h"
#include <cmath>

void MovingPlatform::Draw() const {
    Platform::Draw();
}

void MovingPlatform::UpdatePosition(float dt){
    Platform::UpdatePosition(dt);

    theta += GetFrameTime();
    float offsetX = std::cos(theta);
    position.x += offsetX;
    bounds.x = position.x;
}