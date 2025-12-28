#pragma once
#include <vector>
#include <memory>
#include "raylib.h"


// Forward declarations
class Pickup;
class Character;
class EffectSystem;


// Classe per gestire tutti i pickup presenti nel gioco
class PickupManager {

    public :
        // Tipi di Pickup disponibili
        enum class Type { Coin, Spring, Slow };

        // Parametri di Spawn (decisi dal gameplay)
        // Valori inizializzati di default
        struct SpawnInfo
        {
            Vector2 pos{};
            float radius = 10.0f;
            int intValue = 1;
            float value = 1.0f;
            float duration = 0.0f;
        };


    private:
        // Vettore di puntatori unici ai pickup
        // aggiunge : push_back
        // rimuove : erase 
        // unique_ptr 
        std::vector<std::unique_ptr<Pickup>> pickups;  // Vettore di puntatori unici ai pickup

        // Aggiunge un pickup generico
        void Add(std::unique_ptr<Pickup> pickup);


    public:
        
        // Metodo unico di spawn
        void Spawn(Type type, const SpawnInfo& info);

        // Ciclo di vita dei pickup
        // Aggiorna lo stato, controlla le collisioni, attiva gli effetti e rimuove i pickup raccolti
        void Update(float dt, Character& character, EffectSystem& effects);
        // Disegna tutti i pickup attivi
        void Draw() const;


        // Utility
        // Rimuove tutti i pickup
        void Clear();
        // Restituisce il numero di pickup attuali
        int Count() const;

};