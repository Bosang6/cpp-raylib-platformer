#pragma once
#include "raylib.h"
#include "math.h"

class Character;
class EffectSystem;

class Pickup {
protected:
    Vector2 position{};
    float radius;
    bool collected{false};
    float animTime = 0.0f;
    
    // Sprite Sheet condiviso per tutti i pickup
    static Texture2D spriteSheet;
    static bool textureLoaded;
    static int instanceCount;
    
    Rectangle currentFrame;
    int frameIndex;
    float frameTime;
    Color tint; 

public:
    Pickup(Vector2 pos, float r, Color tintColor);  
    virtual ~Pickup();
    
    virtual void Update(float dt);
    virtual void Draw() const = 0;
    virtual void OnCollect(Character& character, EffectSystem& effects) = 0;
    
    bool IsCollected() const { return collected; }
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool CheckCollisionPlayer(const Rectangle& charBounds) const;
    virtual const char* GetCollectMessage() const { return nullptr; }
    static float moveDownVelocity;

protected:
    float BonusPulseScale(float speed = 6.0f, float amount = 0.12f) const;
    float MalusShakeX(float speed = 14.0f, float pixel = 2.0f) const;
    
    static void LoadSpriteSheet();
    static void UnloadSpriteSheet();
};