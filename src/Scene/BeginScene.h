#pragma once
#include "ISceneUpdate.h"
#include "raylib.h"

class BeginScene : public ISceneUpdate {

public: 
    void Update() override;
};