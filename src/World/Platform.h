#pragma once
#include "raylib.h"
#include "GameObject.h"

enum class E_PlatformType{
    Solid,
    Breakable,
    Moving
};

class Platform : public GameObject {
protected:
    Rectangle bounds{};
    E_PlatformType type{};
    static constexpr float width{80.0f};
    static constexpr float height{20.0f};
    float moveDownVelocity{125.0f};
    
    // Texture statiche
    static Texture2D textureNormal;
    static Texture2D textureBreakable;
    static Texture2D textureMoving;
    static bool texturesLoaded;

public:
    Platform(const Vector2& pos, E_PlatformType t = E_PlatformType::Solid);
    virtual ~Platform();

    virtual void Draw() const;
    virtual void UpdatePosition(float dt);
    const Rectangle& GetBounds() const;
    Vector2 GetSurfaceCenter() const;
    const E_PlatformType GetType() const;
    
    static void LoadTextures();
    static void UnloadTextures();
};