#pragma onece
#include "ISceneUpdate.h"
#include "raylib.h"

class GameScene : public ISceneUpdate
{
public:
    void Update() override;
};


