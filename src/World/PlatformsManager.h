#pragma once
#include "Platform.h"
#include "BreakablePlatform.h"
#include <random>
#include "Scene/Game.h"
#include <deque>
#include <vector>
#include <memory>

class PlatformsManager {
public:
    static PlatformsManager& GetInstance();

    void GeneratePlatforms();
    void DeletePlatforms();
    void DrawPlatforms();
    void UpdatePlatformsPosition();
    void CheckDelete();

    // api
    std::vector<const Rectangle*> GetPlatformsBound() const;
    
private:
    PlatformsManager() = default;
    ~PlatformsManager() = default;

    float RandFloat(const float a, const float b);
    void GenerateOne();
private:
    //std::deque<Platform> platforms;
    std::deque<std::unique_ptr<Platform>> platforms;

    //----- data for generate platforms ------
    float lastGeneratedY{static_cast<float>(Game::height)};

    // delete distance
    float marginTop{200.0f};
    float marginBottom{200.0f};

    // just test
    float maxVerticleVelocity = -500.0f;
    float moveSpeed = 300.0f; 
    float gravity = 980.0f;

    // Max distance
    
    /*
        H = v0^2 / 2g * 2(jump twice)
    */
    float playerMaxJumpVertical{maxVerticleVelocity * maxVerticleVelocity / gravity};
    /*
        Single Jump max distance
        Dx = moveSpeed * T_max
           = moveSpeed * (2v0 / g)
    */
    float playerMaxJumpHorizontal{moveSpeed * 2 * maxVerticleVelocity / gravity};

    // platform distance
    float minGapY{30.0f};
    float maxGapY{playerMaxJumpVertical};

    // random
    std::mt19937 rng{std::random_device{}()};

    //------------------------------------------

};