#include "raylib.h"
#include "Game.h"
#include "ISceneUpdate.h"
#include "GameScene.h"
#include "EndScene.h"

Game::Game(){
    //initialize window
    InitWindow(800, 450, "Game");
    SetTargetFPS(60);
    currentScene = new BeginScene();
}

Game::~Game(){
    delete currentScene;
}

void Game::Start(){
    //game loop
    while(!WindowShouldClose()){
        //input handling --> TODO
        //------------- Just Test ---------------
        if(IsKeyPressed(KEY_ENTER)){
            ChangeScene(E_SceneType::Game);
        }

        if(IsKeyPressed(KEY_SPACE)){
            ChangeScene(E_SceneType::End);
        }
        //---------------------------------------
        currentScene->Update();
    }
}

void Game::ChangeScene(const E_SceneType type){
    delete currentScene;
    switch (type)
    {
    case E_SceneType::Begin:
        currentScene = new BeginScene();
        break;
    case E_SceneType::Game:
        currentScene = new GameScene();
        break;
    case E_SceneType::End:
        currentScene = new EndScene();
        break;
    }
}