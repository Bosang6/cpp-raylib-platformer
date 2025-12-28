#pragma once
#include "raylib.h"
#include "GameObject.h"


class Platform : public GameObject {

public:
    Platform(const Vector2& pos)
        : GameObject(pos) {}

    void Draw() const override;
};