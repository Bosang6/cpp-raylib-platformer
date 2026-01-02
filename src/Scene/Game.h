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

public:
    // window size
    const static int width{800};
    const static int height{450};
    // current scene pointer
    ISceneUpdate *currentScene;

    Game();
    ~Game();
    void Start();
    void ChangeScene(const E_SceneType type);
    
};