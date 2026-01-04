#include "Pickup.h"
#include "cmath"


// Metodo per controllare collisione cerchio (pickup) vs rettangolo (character)
bool Pickup::CheckCollisionPlayer(const Rectangle& charBounds) const {
    
    // Collisione cerchio (player) vs rettangolo (player)
    return CheckCollisionCircleRec(position, radius, charBounds);
    
}


void Pickup::Update(float dt){
    animTime += dt;
    position.y += dt*moveDownVelocity;
}

