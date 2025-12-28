#pragma onece
#include "ISceneUpdate.h"
#include "raylib.h"
#include "World/PlatformsManager.h"

class GameScene : public ISceneUpdate
{
public:
    GameScene();
    void Update() override;

private:
    void GameInit();

private:
    PlatformsManager& platformsManager = PlatformsManager::GetInstance();
};


