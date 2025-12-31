#include "BreakablePlatform.h"

void BreakablePlatform::Draw() const {
    if(broken) return;

    unsigned char alpha = static_cast<unsigned char>(255 *(breakTimer/breakDelay));
    Color c{230, 41, 55, alpha};
    DrawRectangleRounded(bounds, 0.2f, 10, c);
}

void BreakablePlatform::UpdatePosition(float dt){
    if(broken) return;

    Platform::UpdatePosition(dt);

    // timer
    if(triggered && !broken){
        breakTimer -= dt;
        if(breakTimer < 0.0){
            broken = true;
        }
    }
}

// called when the character collide a breakable platform
void BreakablePlatform::TriggerBreak(){
    if(!triggered && !broken){
        triggered = true;
        breakTimer = 50.0f;
    }
}

bool BreakablePlatform::IsBroken() const {
    return broken;
}