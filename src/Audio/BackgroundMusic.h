#pragma once
#include "raylib.h"

class BackgroundMusic{
public:
    BackgroundMusic(const char* path);
    void Init();
    void Play();
    void Close();

private:
    Music music;
    const char* path;
};