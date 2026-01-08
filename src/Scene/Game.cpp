#include "raylib.h"
#include "Game.h"
#include "ISceneUpdate.h"
#include "GameScene.h"
#include "EndScene.h"

Game::Game(){
    //initialize window
    InitWindow(width, height, "Game");
    SetTargetFPS(60);
    currentScene = new BeginScene();
}

Game::~Game(){
    delete currentScene;
    currentScene = NULL;
}

void Game::Start(){
    //game loop
    while(!WindowShouldClose()){
        // change scene 
        if(currentSceneType == E_SceneType::Begin && IsKeyPressed(KEY_ENTER)){
            ChangeScene(E_SceneType::Game);
        }
        else if(currentSceneType == E_SceneType::Game){
            if(!dynamic_cast<GameScene*>(currentScene)->GetIsRunning()){
                // Salva il punteggio prima di cambiare scena
                float finalScore = dynamic_cast<GameScene*>(currentScene)->GetScore();
                ChangeScene(E_SceneType::End, finalScore);
            }
        }
        else if(currentSceneType == E_SceneType::End && IsKeyPressed(KEY_ENTER)){
            ChangeScene(E_SceneType::Begin);
        }
        currentScene->Update();
    }
}

void Game::ChangeScene(const E_SceneType type, float scoreData){
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
        currentScene = new EndScene(scoreData);
        break;
    }
    currentSceneType = type;
}

void Game::SetSceneTyoe(E_SceneType sceneType){
    currentSceneType = sceneType;
}