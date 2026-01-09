#pragma once
#include "Platform.h"
#include "BreakablePlatform.h"
#include "MovingPlatform.h"
#include <random>
#include "Scene/Game.h"
#include <deque>
#include <vector>
#include <memory>

class PlatformsManager {
public:
    static PlatformsManager& GetInstance();

    void Init();
    void GeneratePlatforms();
    void DeletePlatforms();
    void DrawPlatforms();
    void UpdatePlatformsPosition(float dt);
    void CheckDelete();
    Vector2 GetFirstPlatformPosition();

    // api
    const std::deque<std::unique_ptr<Platform>>& GetPlatforms() const;
    
private:
    PlatformsManager() = default;
    ~PlatformsManager();

    float RandFloat(const float a, const float b);
    void GenerateOne();
private:
    // front : the highest platform
    //  back : the bottommost platform
    std::deque<std::unique_ptr<Platform>> platforms;

    //----- data for generate platforms ------

    /* 
    Save the y-coordinate of the topmost platform. 
    When this value is greater than 10.0f, create a new platform.
    */
    float lastGeneratedY{static_cast<float>(Game::height)};

    // delete distance
    float marginTop{200.0f};
    float marginBottom{200.0f};

    
    // Max distance
    float maxVerticleVelocity{-500.0f};
    float moveSpeed{150.0f}; 
    float gravity{980.0f};
    /*
        H = v0^2 / 2g
    */
    float playerMaxJumpVertical{maxVerticleVelocity * maxVerticleVelocity / (2 * gravity) * 0.9f};
    /*
        Single Jump max distance
        Dx = moveSpeed * T_max
           = moveSpeed * (2v0 / g)
    */
    float playerMaxJumpHorizontal{moveSpeed * 2 * maxVerticleVelocity / gravity};

    // platform distance
    float minGapY{80.0f};
    float maxGapY{playerMaxJumpVertical};

    // random
    std::mt19937 rng{std::random_device{}()};

    //------------------------------------------

};