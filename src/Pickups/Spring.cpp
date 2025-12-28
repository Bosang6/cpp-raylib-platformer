#include "Spring.h"
#include "raylib.h"
#include "Character/Character.h"


// Costruttore dello spring
Spring::Spring(Vector2 pos, float radius, float jumpMultiplier)
    : Pickup(pos, radius), jumpMultiplier(jumpMultiplier) {}


void Spring::Update(float dt) {
    // Per ora niente anicamzioni
}


void Spring::Draw() const {
    // Disegno dello spring come un cerchio verde
    DrawCircleV(position, radius, GREEN);
    DrawCircleLines(
        (int)position.x,
        (int)position.y,
        radius,
        DARKGREEN
    );

    // Disegno di una molla stilizzata
    DrawLine((int)position.x - radius * 0.5f, (int)position.y,
             (int)position.x + radius * 0.5f, (int)position.y, DARKGREEN);

}

// Spring scope : potenzia SOLO il prossimo salto (one-shot), poi si resetta nel Character
void Spring::OnCollect(Character& character, EffectManager& ) {

    collected = true;
    // character.SetNextJumpMultiplier(jumpMultiplier);

    // Nel Character inserire : 
    /*
        variabile privata nextJumpMultiplier = 1.0f;
        e 2 medoti:
        void SetNextJumpMultiplier(float m)
        float ConsumeNextJumpMultiplier()  
    */

    /*
        void Character::SetNextJumpMultiplier(float m){
            if (m > nextJumpMultiplier) nextJumpMultiplier = m;
        }
    */ 

    /*
        float Character::ConsumeNextJumpMultiplier() {
            float m = nextJumpMultiplier;
            nextJumpMultiplier = 1.0f
            return m
        }
    */

    /*  Nel punto del salto
        if (IsKeyPressed(KEY_SPACE) && onGround)
        {
            float mult = ConsumeNextJumpMultiplier();
            velocity.y = -jumpForce * mult;
            onGround = false;
        }
    */


    // Implementazione futura : effetto sonoro e visivo

}


