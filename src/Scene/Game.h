#pragma once
#include "ISceneUpdate.h"
#include "BeginScene.h"

enum class E_SceneType{
    Begin,
    Game,
    End
};

class Game{
public:
    Game();
    ~Game();
    void Start();
    void ChangeScene(const E_SceneType type, float scoreData = 0.0f);
    void SetSceneTyoe(E_SceneType sceneType);

public:
    // window size
    const static int width{600};
    const static int height{800};
    // current scene pointer
    ISceneUpdate *currentScene;

private:
    E_SceneType currentSceneType{E_SceneType::Begin};
};