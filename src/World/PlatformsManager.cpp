#include "PlatformsManager.h"

PlatformsManager& PlatformsManager::GetInstance() {
    static PlatformsManager instance;
    return instance;
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
    float newX = RandFloat(20.0f, Game::width - 100); // Platform Size: 80*20

    // ---make sure player can jump to the new platform---
    // float flag = RandFloat(-1.0f, 1.0f);
    // float preX = platforms.front().position.x;
    // if(flag < 0.0f && preX > 40.0f){
    //     newX = preX + flag * playerMaxJumpHorizontal;
    // }
    // else{
    //     newX = preX + 80.0f + flag * playerMaxJumpHorizontal;
    // }

    float generateProbablity = RandFloat(0.0f, 10.0f);

    // Generate a BreakablePlatform with 30% probability
    if(generateProbablity > 7.0f && generateProbablity < 10.0f){
        platforms.push_front(std::make_unique<BreakablePlatform>(Vector2{newX, newY}));
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

void PlatformsManager::UpdatePlatformsPosition() {
    for(auto& platform : platforms){
        platform->UpdatePosition(0.5f);
    }
    lastGeneratedY = platforms.front()->position.y;
}

// ------- api ----------

// Platform vector using for collision detection
const std::deque<std::unique_ptr<Platform>>& PlatformsManager::GetPlatforms() const{
    return platforms;
}