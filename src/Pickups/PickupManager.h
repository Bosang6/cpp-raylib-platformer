#pragma once
#include <vector>
#include <memory>
#include "raylib.h"

// Forward declarations
class Pickup;
class Character;
class EffectManager;

// Classe per gestire tutti i pickup presenti nel gioco
class PickupManager {

    private:
        // Vettore di puntatori unici ai pickup
        // aggiunge : push_back
        // rimuove : erase 
        // unique_ptr 
        std::vector<std::unique_ptr<Pickup>> pickups;  // Vettore di puntatori unici ai pickup


    public:
        // Aggiunge un pickup generico, utile per estensioni future
        void Add(std::unique_ptr<Pickup> pickup);

        // Helper : spawn di una moneta in una pos, con un raggio ed un ammontare specifico
        void SpawnCoin(Vector2 pos, float radius = 10.0f, int amount = 1);

        // Helper : spawn di uno spring in una pos, con un raggio ed una forza di boost specifica
        void SpawnSpring(Vector2 pos, float radius = 10.0f, float boostAmount = 600.0f);

        // Ciclo di vita dei pickup
        // Aggiorna lo stato, controlla le collisioni, attiva gli effetti e rimuove i pickup raccolti
        void Update(float dt, Character& character, EffectManager& effects);
        // Disegna tutti i pickup attivi
        void Draw() const;


        // Utility
        // Rimuove tutti i pickup
        void Clear();
        // Restituisce il numero di pickup attuali
        int Count() const;

};