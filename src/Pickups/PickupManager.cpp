#include "PickupManager.h"
#include "Pickup.h"
#include "Coin.h"
#include "Spring.h"
#include "Slow.h"
#include "ScoreMultiplier.h"
#include "Character/Character.h"
#include "EffectSystem.h"
#include <algorithm>


// Trasferisce la proprietà del pickup al vettore dei pickup
void PickupManager::Add(std::unique_ptr<Pickup> pickup) {
    // std::move : trasferisce la proprietà del puntatore unico al vettore
    pickups.push_back(std::move(pickup));
}


// Crea e registra un pickup del tipo specificato utilizzando i parametri forniti dallo SpawnInfo.
// Delego al gameplay la decisione di quando e dove spawnarlo
void PickupManager::Spawn(Type type, const SpawnInfo& info){

    switch (type)
    {
        case Type::Coin:
            Add(std::make_unique<Coin>(info.pos, info.radius, info.intValue));
            break;

        case Type::Spring:
            Add(std::make_unique<Spring>(info.pos, info.radius, info.value));
            break;

        case Type::Slow:
            Add(std::make_unique<Slow>(info.pos, info.radius, info.value, info.duration));
            break;

        case Type::ScoreMultiplier:
            Add(std::make_unique<ScoreMultiplier>(info.pos, info.radius, info.value, info.duration));
            break;

    }
    
}



void PickupManager::Update(float dt, Character& character, EffectSystem& effects) {
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
