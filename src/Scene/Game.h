#pragma once
#include "ISceneUpdate.h"
#include "BeginScene.h"

enum class E_SceneType{
    Begin,
    Game,
    End
};

class Game{
private:
    E_SceneType currentSceneType{E_SceneType::Begin};
public:
    // window size
    const static int width{600};
    const static int height{800};
    // current scene pointer
    ISceneUpdate *currentScene;

    Game();
    ~Game();
    void Start();
    void ChangeScene(const E_SceneType type);
    void SetSceneTyoe(E_SceneType sceneType);
};