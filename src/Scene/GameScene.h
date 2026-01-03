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
    float GetScore() const;
    //void AddScore(float amount);

private:
    void GameInit();

private:
    bool isRunning{false};
    PlatformsManager& platformsManager = PlatformsManager::GetInstance();
    PickupManager pickupManager;
    EffectSystem effects;
    float instructionsTimer{5.0f};
    
    // Sistema di punteggio
    float score{0.0f};
    float scoreIncrement{10.0f};

    // Dichiarazione delle funzioni
    void UpdateScore(float deltaTime);
    void DrawScore();
};


