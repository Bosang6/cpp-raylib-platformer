#pragma once
#include "raylib.h"

//Forward declaration 
class Character;
class EffectManager;

// Classe base astratta per qualsiasi pickup nel gioco
class Pickup{

    protected:
        Vector2 position{};              // Posizione del pickup
        float radius{10.0f};            // Raggio del pickup
        bool collected{false};          // Stato di raccolta del pickup


    public:
        // Costruttore base
        Pickup(Vector2 pos, float r = 10.0f) : position(pos), radius(r) {}

        // Distruttore virtuale
        virtual ~Pickup() = default;


        // Metodo per aggiornare lo stato del pickup
        virtual void Update(float dt) {}


        // Disegna il pickup
        virtual void Draw() const = 0;


        // Cosa succede quando viene raccolto
        virtual void OnCollect(Character& character, EffectManager& effects) = 0;


        // Utility
        bool IsCollected() const { return collected; };
        Vector2 GetPosition() const { return position; }
        float GetRadius() const { return radius; };


        // Collisione cerchio - rettangolo
        bool CheckCollisionPlayer(const Rectangle& charBounds) const;

};
