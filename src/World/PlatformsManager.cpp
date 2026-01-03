#include "PlatformsManager.h"

PlatformsManager& PlatformsManager::GetInstance() {
    static PlatformsManager instance;
    return instance;
}

void PlatformsManager::Init(){
    platforms.clear();
    lastGeneratedY = Game::height;
}

void PlatformsManager::GeneratePlatforms() {
    while(lastGeneratedY > 10.0f){
        GenerateOne();
    }
}

void PlatformsManager::DeletePlatforms() {
    platforms.clear();
}

void PlatformsManager::DrawPlatforms() {
    for(auto& platform : platforms) {
        platform->Draw();
    }
}

float PlatformsManager::RandFloat(const float a, const float b){
    std::uniform_real_distribution<float> dist(a, b);
    return dist(rng); 
}

// Generate a new platform at the top of the screen
void PlatformsManager::GenerateOne(){
    float gapY = RandFloat(minGapY, maxGapY);
    gapY = std::min(gapY, playerMaxJumpVertical);

    float newY = lastGeneratedY - gapY;
    float newX = RandFloat(20.0f, Game::width - 100.0f);

    // ---make sure player can jump to the new platform---
    if(!platforms.empty()){
        Platform* firstPlatform = platforms.front().get();
        float center = firstPlatform->GetSurfaceCenter().x;
        float left = center + playerMaxJumpHorizontal - 40.0f;
        left = left < 20.0f ? 20.0f : left;
        float right = center - playerMaxJumpHorizontal + 40.0f;
        right = (right < Game::width - 100) ? right : (Game::width - 100);
        newX = RandFloat(left, right); // Platform Size: 80*20
    }

    // generate a platform
    float generateProbablity = RandFloat(0.0f, 10.0f);
    E_PlatformType t = E_PlatformType::Solid;
    if(platforms.size() > 0)
        t = platforms.front().get()->GetType();
    // Generate a BreakablePlatform with 30% probability and the last platform generated was not breakable.
    if(generateProbablity > 7.0f && generateProbablity < 10.0f && t != E_PlatformType::Breakable){
        platforms.push_front(std::make_unique<BreakablePlatform>(Vector2{newX, newY}));
    }
    else if(generateProbablity > 4.0f && generateProbablity <= 7.0f){
        platforms.push_front(std::make_unique<MovingPlatform>(Vector2{newX, newY}, RandFloat(0.0f, 1.0f)));
    }
    else{
        platforms.push_front(std::make_unique<Platform>(Vector2{newX, newY}));
    }

    lastGeneratedY = newY;
}

// Deleting platforms outside the boundary recursively
void PlatformsManager::CheckDelete() {
    if(!platforms.empty()){
        Platform& last = *platforms.back();
        if(last.position.y > Game::height + marginBottom){
            platforms.pop_back();
            PlatformsManager::CheckDelete();
        }
    }
}

void PlatformsManager::UpdatePlatformsPosition(float dt) {
    for(auto& platform : platforms){
        platform->UpdatePosition(dt);
    }
    lastGeneratedY = platforms.front()->position.y;
}

// ------- api ----------

// using for collision detection
const std::deque<std::unique_ptr<Platform>>& PlatformsManager::GetPlatforms() const{
    return platforms;
}