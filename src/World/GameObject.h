#pragma once
#include "raylib.h"

class GameObject {
public:
    GameObject(const Vector2& pos)
        : position(pos) {};
    virtual ~GameObject() = default;

    // GameObject(const Vector2& pos, const Texture2D& tex)
    //     : position(pos), texture(tex) {}

    virtual void Draw() const = 0;

public: 
    Vector2 position;
    //Texture2D texture;
};