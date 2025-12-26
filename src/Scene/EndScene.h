#pragma onece
#include "ISceneUpdate.h"
#include "raylib.h"

class EndScene : public ISceneUpdate
{
public:
    void Update() override;
};