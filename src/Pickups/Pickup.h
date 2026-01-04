#pragma once
#include "raylib.h"
#include "math.h"

//Forward declaration 
class Character;
class EffectSystem;

// Classe base astratta per qualsiasi pickup nel gioco
class Pickup{

    protected:
        Vector2 position{};              // Posizione del pickup
        float radius;            // Raggio del pickup
        bool collected{false};          // Stato di raccolta del pickup

        float animTime = 0.0f;
        float moveDownVelocity{50.0f};

    public:
        // Costruttore base
        Pickup(Vector2 pos, float r) : position(pos), radius(r) {}

        // Distruttore virtuale
        virtual ~Pickup() = default;


        // Metodo per aggiornare lo stato del pickup
        virtual void Update(float dt);


        // Disegna il pickup
        virtual void Draw() const = 0;


        // Cosa succede quando viene raccolto
        virtual void OnCollect(Character& character, EffectSystem& effects) = 0;


        // Utility
        bool IsCollected() const { return collected; };
        Vector2 GetPosition() const { return position; }
        float GetRadius() const { return radius; };


        // Collisione cerchio - rettangolo
        bool CheckCollisionPlayer(const Rectangle& charBounds) const;

        // 
        virtual const char* GetCollectMessage() const { return nullptr; }


    protected:

        // Bonus : Pulse morbido
        float BonusPulseScale(float speed = 6.0f, float amount = 0.12f) const{
            return 1.0f + sinf(animTime * speed) * amount;
        }

        // Malus : Shake orizzontale
        float MalusShakeX(float speed = 14.0f, float pixel = 2.0f) const{
            return sinf(animTime * speed) * pixel;
        }


};
