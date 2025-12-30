#include "BreakablePlatform.h"

void BreakablePlatform::Draw() const {
    if(broken) return;

    Color c = triggered ? YELLOW : RED;
    DrawRectangleRounded(bounds, 0.2f, 10, c);
}

void BreakablePlatform::UpdatePosition(float dt){
    if(broken) return;

    Platform::UpdatePosition(dt);

    // timer
    if(triggered && !broken){
        breakTimer += dt;
        if(breakTimer > breakDelay){
            broken = true;
        }
    }
}

// called when the character collide a breakable platform
void BreakablePlatform::TriggerBreak(){
    if(!triggered && !broken){
        triggered = true;
        timer = 0.0f;
    }
}

bool BreakablePlatform::IsBroken() const {
    return broken;
}