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
    float moveDownVelocity{50.0f};

public:
    Platform(const Vector2& pos, E_PlatformType t = E_PlatformType::Solid)
        : GameObject(pos) , bounds{pos.x, pos.y, width, height}, type{t} {}

    void Draw() const override;
    virtual void UpdatePosition(float dt);
    const Rectangle& GetBounds() const;
    Vector2 GetSurfaceCenter() const;
    const E_PlatformType GetType() const;
};