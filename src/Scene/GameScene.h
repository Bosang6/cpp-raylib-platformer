#pragma onece
#include "ISceneUpdate.h"
#include "raylib.h"
#include "World/PlatformsManager.h"

#include "Character/Playable_character.h"
#include "Pickups/PickupManager.h"
#include "Pickups/EffectSystem.h"


class GameScene : public ISceneUpdate
{
public:
    GameScene();
    void Update() override;
    PlayableCharacter player{{200, 100}, {30, 50}};
    bool GetIsRunning() const;
    void SetIsRuning(bool isRunning);

private:
    void GameInit();

private:
    bool isRunning{false};
    PlatformsManager& platformsManager = PlatformsManager::GetInstance();
    PickupManager pickupManager;
    EffectSystem effects;
};


