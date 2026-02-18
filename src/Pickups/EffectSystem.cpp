#include "EffectSystem.h"


void EffectSystem::AddEffect(EffectType type, float durationSeconds, float value) {
    // Controllo se l'effetto è già presente
    for (auto& e : effects) {
        if (e.type == type) {
            // Aggiorno il timer e il valore
            e.remainingTime = durationSeconds;
            e.value = value;
            return;
        }
    }


    // Se non è presente, lo aggiungo
    EffectInstance newEffect;
    newEffect.type = type;
    newEffect.remainingTime = durationSeconds;
    newEffect.value = value;
    effects.push_back(newEffect);

}


void EffectSystem::Update(float dt) {
    
    for (auto& e : effects) {
        e.remainingTime -= dt;
    }

    // Rimuove tutti gli oggetti scaduti
    effects.erase(
        std::remove_if(
            effects.begin(),
            effects.end(),
            [](const EffectInstance& e) { return e.remainingTime <= 0.0f; }
        ),
        effects.end()
    );

}



void EffectSystem::ClearAllEffects() {
    effects.clear();
}



int EffectSystem::CountActiveEffects() const {
    return static_cast<int>(effects.size());
}


// --- Effetti 
// Gestisco tutti gli effetti qui per non avere problami di stacking 


// Ritorna il moltiplicatore di velocità del player.
// Se non ci sono effetti Slow attivi -> 1.0 (velocità normale).
// Se ci sono più Slow -> viene applicato quello che rallenta di più.
float EffectSystem::GetSpeedMultiplier() const {
    
    float slowMultiplier = 1.0f;

    for (const auto& e : effects) {
        if (e.type == EffectType::Slow) {
            if(e.value < slowMultiplier){
                slowMultiplier = e.value;
            }
        }
    }

    return slowMultiplier;
}


// Ritorna il moltiplicatore di punteggio
// Stesso pattern di Slow ma applicato al punteggio
float EffectSystem::GetScoreMultiplier() const {

    float scoreMultiplier = 1.0f;

    for(const auto& e : effects){
        if(e.type == EffectType::ScoreMultiplier){
            if(e.value > scoreMultiplier){
                scoreMultiplier = e.value;
            }
        }
    }

    return scoreMultiplier;
    
}

bool EffectSystem::IsReverseControlActive() const {
    for (const auto& e : effects){
        if(e.type == EffectType::ReverseControl && e.remainingTime > 0.0f)
            return true;
    }
    return false;
}

// Restituisce una copia "read-only" degli effetti attivi per la UI
std::vector<EffectSystem::ActiveEffectInfo> EffectSystem::GetActiveEffects() const
{
    std::vector<ActiveEffectInfo> out;
    out.reserve(effects.size());

    for (const auto& e : effects)
        out.push_back({ e.type, e.remainingTime, e.value });

    return out;
}



