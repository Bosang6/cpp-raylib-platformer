#include "Platform.h"

class BreakablePlatform : public Platform{
private:
    bool broken{false};
    bool triggered{false};
    float breakDelay = 1.0f;
    float timer{0.0f};
    float breakTimer{3.0f};

public:
    BreakablePlatform(const Vector2& pos) 
        : Platform(pos, E_PlatformType::Breakable) {}

    void Draw() const override;
    void UpdatePosition(float dt) override;

    void TriggerBreak();
    bool IsBroken() const;

};