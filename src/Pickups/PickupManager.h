#pragma once
#include <deque>
#include <memory>
#include <random>
#include <unordered_map>
#include <string>

#include "raylib.h"
#include "Pickup.h"
#include "Scene/Game.h"

class Pickup;
class Character;
class EffectSystem;
class UIPickMessage;


// Classe responsabile della gestione di tutti i Pickup nel gioco
class PickupManager {

    public :
        // Tipi di Pickup attualmente disponibili
        enum class Type { Coin, Spring, Slow, ScoreMultiplier } ;


        // Struttura contenente i valori di default
        struct Defaults
        {
            float radius = 12.f;

            // Coin
            int coinValue  = 100;

            // Slow
            float slowMultiplier  = 0.6f;
            float slowDuration = 12.f;

            // Spring
            float jumpMultiplier = 1.6f;

            // ScoreMultiplier
            float scoreMultiplier = 2.f;
            float scoreDuration = 15.f;
        };

        
    private:
        
        Defaults defaults; 
        
        //  Permette inserimenti/rimozioni sia in testa che in coda 
        std::deque<std::unique_ptr<Pickup>> pickups;
        void Add(std::unique_ptr<Pickup> pickup);

        float lastGeneratedY{Game::height};
        std::mt19937 rng{std::random_device{}()};

        bool soundsLoaded = false;
        std::unordered_map<std::string, Sound> sound;


    public:

        void Update(float dt, Character& character, EffectSystem& effects, float& score, UIPickMessage& ui);

        void Draw() const;

        void Clear();

        int Count() const;

        void GeneratePickups();

        void CheckDelete();

        void InitSounds();

        void UnloadSounds();

    private:

        float RandFloat(const float a, const float b);
        int RandInt(const int a, const int b);
        void Spawn(Type type, Vector2 pos);

};