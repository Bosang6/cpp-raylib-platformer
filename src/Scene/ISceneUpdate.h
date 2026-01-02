#pragma once
class ISceneUpdate{
public:
    virtual ~ISceneUpdate() = default;
    virtual void Update() = 0;
};