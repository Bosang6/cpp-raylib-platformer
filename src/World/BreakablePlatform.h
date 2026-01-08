#include "Platform.h"

class BreakablePlatform : public Platform{
public:
    BreakablePlatform(const Vector2& pos) 
        : Platform(pos, E_PlatformType::Breakable) {}

    void Draw() const override;
    void UpdatePosition(float dt) override;

    void TriggerBreak();
    bool IsBroken() const;

private:
    bool broken{false};
    bool triggered{false};
    float breakDelay{50.0f}; // Used to calculate alpha
    float breakTimer{50.0f};
};