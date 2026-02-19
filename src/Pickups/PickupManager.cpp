#include <algorithm>

#include "PickupManager.h"
#include "Pickup.h"
#include "Coin.h"
#include "Spring.h"
#include "Slow.h"
#include "ScoreMultiplier.h"
#include "ReverseControl.h"
#include "Character/Character.h"
#include "EffectSystem.h"
#include "UI/UIPickMessage.h"


// Trasferisce la proprietà del pickup al vettore dei pickup.
// std::unique_ptr garantisce ownership esclusiva e distruzione automatica.
void PickupManager::Add(std::unique_ptr<Pickup> pickup) {

    pickups.push_back(std::move(pickup));

}


// Crea e registra un pickup del tipo specificato utilizzando i parametri forniti dallo SpawnInfo.
// Delego al gameplay la decisione di quando e dove spawnarlo
void PickupManager::Spawn(Type type, Vector2 pos){

    switch (type)
    {
        case Type::Coin:
            Add(std::make_unique<Coin>(pos, defaults.radius, defaults.coinValue));
            break;

        case Type::Spring:
            Add(std::make_unique<Spring>(pos, defaults.radius, defaults.jumpMultiplier));
            break;

        case Type::Slow:
            Add(std::make_unique<Slow>(pos, defaults.radius, defaults.slowMultiplier, defaults.slowDuration));
            break;

        case Type::ScoreMultiplier:
            Add(std::make_unique<ScoreMultiplier>(pos, defaults.radius, defaults.scoreMultiplier, defaults.scoreDuration));
            break;

        case Type::ReverseControl:
            Add(std::make_unique<ReverseControl>(pos,defaults.radius, defaults.reverseDuration)); 
            break;
    }
    
}


// Aggiorna tutti i Pickups, controlla la collisione con il ch e gestisce la raccolta.
// Se raccolto : applica l'effetto (OnCollect) e mostra messaggio UI.
void PickupManager::Update(float dt, Character& character, EffectSystem& effects, float& score, UIPickMessage& ui) {
    
    // 1. Updtate + Collisione
    for(auto& p : pickups) {
        // p è un reference(&) a un puntatore unico (unique_ptr<Pickup>)
        // dereferenzia il puntatore ed accede al metodo Update
        p->Update(dt);

        
        if (!p->IsCollected() && p->CheckCollisionPlayer(character.GetBounds()))
        {
            Vector2 msgPos = p->GetPosition();
            msgPos.y -= 30.f;

            p->OnCollect(character, effects);

            if (const char* id = p->GetCollectSound())
            {
                auto it = sound.find(id);
                if (it != sound.end()) PlaySound(it->second);
            }

            if(auto coin = dynamic_cast<Coin*>(p.get()))
            {
                float added = coin->GetValue() * effects.GetScoreMultiplier();
                score += added;
                ui.PushAt(TextFormat("Score +%.0f", added), msgPos);
            }
            else
            {
                if(const char* msg = p->GetCollectMessage())
                    ui.PushAt(msg, msgPos);
            }
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

    // 3. Update the last generated pickup position y
    if(!pickups.empty())
        lastGeneratedY = pickups.back().get()->GetPosition().y;
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


float PickupManager::RandFloat(const float a, const float b){
    std::uniform_real_distribution<float> dist(a, b);
    return dist(rng); 
}


int PickupManager::RandInt(const int a, const int b){
    std::uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}


void PickupManager::GeneratePickups(){
    while(lastGeneratedY > 10.0f){
        //random position
        float newX = RandFloat(20.0f, Game::width - 50.0f);
        float newY = RandFloat(lastGeneratedY - 400.0f, lastGeneratedY - 200.0f);

        // random pickup
        int effetType = RandInt(1, 5);
        switch (effetType)
        {
        case 1:
            Spawn(PickupManager::Type::Coin, Vector2{newX, newY});
            break;
        case 2:
            Spawn(PickupManager::Type::ScoreMultiplier, Vector2{newX, newY});
            break;
        case 3:
            Spawn(PickupManager::Type::Slow, Vector2{newX, newY});
            break;
        case 4:
            Spawn(PickupManager::Type::Spring, Vector2{newX, newY});
            break;       
        case 5:
            Spawn(PickupManager::Type::ReverseControl, {newX, newY});
            break;
        }
        //save lastGeneratedY
        lastGeneratedY = newY;
    }
}


void PickupManager::CheckDelete(){
    if(!pickups.empty()){
        Pickup& last = *pickups.front();
        if(last.GetPosition().y > Game::height){
            pickups.pop_front();
            PickupManager::CheckDelete();
        }
    }
}


void PickupManager::InitSounds()
{
    if(soundsLoaded) return;
    soundsLoaded = true;

    sound["coin"] = LoadSound("assets/Audio/Sounds/Coin_Sound.mp3");
    SetSoundVolume(sound["coin"], 0.6f);
    sound["spring"] = LoadSound("assets/Audio/Sounds/JumpBoost_Sound.mp3");
    //SetSoundVolume(sound["spring"], 0.6f);
    sound["slow"] = LoadSound("assets/Audio/Sounds/Slow_Sound.mp3");
    SetSoundVolume(sound["slow"], 1.0f);
    sound["scorex2"] = LoadSound("assets/Audio/Sounds/ScoreMulti_Sound.mp3");
    //SetSoundVolume(sound["scorex2"], 0.6f);
    sound["reverse"] = LoadSound("assets/Audio/Sounds/ReverseControl_Sound.mp3");
    SetSoundVolume(sound["reverse"], 0.6f);
}

void PickupManager::UnloadSounds()
{
    if(!soundsLoaded) return;
    soundsLoaded = false;

    for (auto& kv : sound) UnloadSound(kv.second);
    sound.clear();
}
