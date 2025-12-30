#pragma once
#include <vector>
#include <memory>
#include "raylib.h"
#include "Pickup.h"


class Pickup;
class Character;
class EffectSystem;


// Classe per gestire tutti i pickup presenti nel gioco
class PickupManager {

    public :
        // Tipi di Pickup disponibili
        enum class Type { Coin, Spring, Slow, ScoreMultiplier } ;


        // Struttura di default
        struct Defaults
        {
            float radius = 10.f;
            // Coin
            int   coinValue  = 10;

            // Slow
            float slowMultiplier  = 0.6f;
            float slowDuration = 4.f;

            // Spring
            float jumpMultiplier = 1.8f;

            // ScoreMultiplier
            float scoreMultiplier = 2.f;
            float scoreDuration = 6.f;
        };


    private:
        
        Defaults defaults; 

        std::vector<std::unique_ptr<Pickup>> pickups;  
        void Add(std::unique_ptr<Pickup> pickup);


    public:
        
        void Spawn(Type type, Vector2 pos);

        void Update(float dt, Character& character, EffectSystem& effects);
        void Draw() const;


        void Clear();
        int Count() const;

};