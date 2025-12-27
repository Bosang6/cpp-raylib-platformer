#include "PickupManager.h"
#include "Pickup.h"
#include "Coin.h"
#include "Spring.h"
#include "Character/Character.h"
#include "EffectManager.h"
#include <algorithm>


// Trasferisce la proprietà del pickup al vettore dei pickup
void PickupManager::Add(std::unique_ptr<Pickup> pickup) {
    // std::move : trasferisce la proprietà del puntatore unico al vettore
    pickups.push_back(std::move(pickup));
}


// Crea una nuova moneta e la aggiunge al vettore dei pickup
void PickupManager::SpawnCoin(Vector2 pos, float radius, int amount) {
    // std::make_unique<Coin>(pos, radius, amount) : alloca una nuova Coin in memoria e chiama il costruttore (pos, radius, amount). Nessun new, nessun delete, zero memory leak.
    // pickups.push_back(...) : aggiunge il puntatore unico appena creato al vettore dei pickup
    pickups.push_back(std::make_unique<Coin>(pos, radius, amount));
}

// Crea un nuovo spring e lo aggiunge al vettore dei pickup
void PickupManager::SpawnSpring(Vector2 pos, float radius, float boostAmount) {
    pickups.push_back(std::make_unique<Spring>(pos, radius, boostAmount));
}


void PickupManager::Update(float dt, Character& character, EffectManager& effects) {
    // 1. Updtate + Collisione
    for(auto& p : pickups) {
        // p è un reference(&) a un puntatore unico (unique_ptr<Pickup>)
        // dereferenzia il puntatore ed accede al metodo Update
        p->Update(dt);

        // Controllo cerchio - rettangolo tra pickup e giocatore
        if(!p->IsCollected() && p->CheckCollisionPlayer(character.GetBounds())) {
            p->OnCollect(character, effects);
        }
    }

    // 2. Rimuovo i pickup raccolti
    pickups.erase(
        std::remove_if(pickups.begin(), pickups.end(),
            [](const std::unique_ptr<Pickup>& p) { 
                return p->IsCollected();
            }),
        pickups.end()
    );
}


void PickupManager::Draw() const {
    for(const auto& p : pickups) {
        p->Draw();
    }
}


void PickupManager::Clear() {
    pickups.clear();
}


int PickupManager::Count() const {
    return static_cast<int>(pickups.size());
}
