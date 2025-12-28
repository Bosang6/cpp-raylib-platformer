#pragma once
#include "Platform.h"
#include <random>
#include "Scene/Game.h"
#include <deque>

class PlatformsManager {
public:
    static PlatformsManager& GetInstance();

    void GeneratePlatforms();
    void DeletePlatforms();
    void DrawPlatforms();
    void UpdatePlatformsPosition();
    void CheckDelete();
    
private:
    PlatformsManager() = default;
    ~PlatformsManager() = default;

    float RandFloat(const float a, const float b);
    void GenerateOne();
private:
    std::deque<Platform> platforms;

    //----- data for generate platforms ------
    float lastGeneratedY{static_cast<float>(Game::height)};

    // platform distance
    float minGapY{30.0f};
    float maxGapY{60.0f};

    // delete distance
    float marginTop{200.0f};
    float marginBottom{200.0f};

    // just test
    float playerMaxJumpVertical{120.0f};
    float playerMaxJumpHorizontal{140.0f};

    // random
    std::mt19937 rng{std::random_device{}()};

    //------------------------------------------

};