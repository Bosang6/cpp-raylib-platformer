#include "MovingPlatform.h"
#include <cmath>

void MovingPlatform::Draw() const {
    if(texturesLoaded && textureMoving.id > 0) {
        // Disegna con texture
        DrawTexturePro(
            textureMoving,
            {0, 0, (float)textureMoving.width, (float)textureMoving.height},
            bounds,
            {0, 0},
            0.0f,
            WHITE
        );
    } else {
        // Fallback
        Platform::Draw();
        
    }
}

void MovingPlatform::UpdatePosition(float dt){
    Platform::UpdatePosition(dt);

    theta += GetFrameTime();
    float offsetX = std::cos(theta);
    position.x += offsetX;
    bounds.x = position.x;
}