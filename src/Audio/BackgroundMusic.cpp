#include "BackgroundMusic.h"

BackgroundMusic::BackgroundMusic(const char* path) : path{path} { }

void BackgroundMusic::Init(){
    InitAudioDevice();
    music = LoadMusicStream(path);
    PlayMusicStream(music);
}

void BackgroundMusic::Play(){
    UpdateMusicStream(music);
}

void BackgroundMusic::Close(){
    UnloadMusicStream(music);
    CloseAudioDevice();
}

