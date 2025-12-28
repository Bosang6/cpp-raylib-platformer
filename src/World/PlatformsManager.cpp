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
        platform.Draw();
    }
}

float PlatformsManager::RandFloat(const float a, const float b){
    std::uniform_real_distribution<float> dist(a, b);
    return dist(rng); 
}

void PlatformsManager::GenerateOne(){
    float gapY = RandFloat(minGapY, maxGapY);
    gapY = std::min(gapY, playerMaxJumpVertical);

    float newY = lastGeneratedY - gapY;
    float newX = RandFloat(20.0f, Game::width - 100); // Platform Size: 80*20

    // ---make sure player can jump to the new platform---
    // float preX = platforms.front().position.x;
    // while(std::abs(newX - preX) > playerMaxJumpHorizontal){
    //     newX = RandFloat(20.0f, Game::width - 100);
    // }

    platforms.push_front(Platform{Vector2{newX, newY}});

    lastGeneratedY = newY;
}

// 
void PlatformsManager::CheckDelete() {
    if(!platforms.empty()){
        Platform& last = platforms.back();
        if(last.position.y > Game::height + marginBottom){
            platforms.pop_back();
            PlatformsManager::CheckDelete();
        }
    }
}

void PlatformsManager::UpdatePlatformsPosition() {
    for(auto& platform : platforms){
        platform.position.y += 0.1f;
    }
    lastGeneratedY = platforms.front().position.y;
}