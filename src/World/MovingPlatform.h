#include "Platform.h"

class MovingPlatform : public Platform{
public:
    MovingPlatform(const Vector2& pos, float theta) 
        : Platform(pos, E_PlatformType::Moving), theta{theta} {}

    void Draw() const override;
    void UpdatePosition(float dt) override;

private:
    float theta{0.0f};
};