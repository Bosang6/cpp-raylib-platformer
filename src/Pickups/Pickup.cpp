#include "Pickup.h"



bool Pickup::CheckCollisionPlayer(const Rectangle& charBounds) const {
    return CheckCollisionCircleRec(position, radius, charBounds);
}


void Pickup::Update(float dt){
    animTime += dt;
    position.y += dt*moveDownVelocity;
}

