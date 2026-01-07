#include "raylib.h"
#include "ScoreMultiplier.h"
#include "EffectSystem.h"



ScoreMultiplier::ScoreMultiplier(Vector2 pos, float radius, float scoreMultiplier, float durationSeconds)
    : Pickup(pos,radius), scoreMultiplier(scoreMultiplier), durationSeconds(durationSeconds) {}


void ScoreMultiplier::Update(float dt){
    Pickup::Update(dt);
}


void ScoreMultiplier::Draw() const {
    
    float s = BonusPulseScale();
    float r = radius * s;
    const char* text = "x2";
    int fontSize = (int)(r * 0.9f);  
    int textWidth = MeasureText(text, fontSize);

    DrawCircleV(position, r, BLUE);
    DrawCircleLines((int)position.x, (int)position.y, r, DARKBLUE);
    DrawText(text, (int)(position.x - textWidth / 2), (int)(position.y - fontSize / 2), fontSize, BLACK);

}



void ScoreMultiplier::OnCollect(Character&, EffectSystem& effects){
    collected = true;

    effects.AddEffect(EffectSystem::EffectType::ScoreMultiplier, durationSeconds, scoreMultiplier);
}


const char* ScoreMultiplier::GetCollectMessage() const {
    return "Score x2";
}

