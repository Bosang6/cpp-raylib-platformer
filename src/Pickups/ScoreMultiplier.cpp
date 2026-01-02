#include "ScoreMultiplier.h"
#include "raylib.h"
#include "EffectSystem.h"


// Costruttore
ScoreMultiplier::ScoreMultiplier(Vector2 pos, float radius, float scoreMultiplier, float durationSeconds)
    : Pickup(pos,radius), scoreMultiplier(scoreMultiplier), durationSeconds(durationSeconds) {}



void ScoreMultiplier::Update(float){}


// Disegna lo ScoreMultiplier pickup
void ScoreMultiplier::Draw() const {
    
    // Cerchio verde
    DrawCircleV(position, radius, GREEN);

    // Testo "x2" al centro
    DrawText("x2",
             (int)(position.x - 10),
             (int)(position.y - 10),
             20,
             BLACK);

}



void ScoreMultiplier::OnCollect(Character&, EffectSystem& effects){
    collected = true;

    effects.AddEffect(EffectSystem::EffectType::ScoreMultiplier, durationSeconds, scoreMultiplier);
}