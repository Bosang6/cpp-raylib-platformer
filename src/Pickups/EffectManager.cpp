#include "EffectManager.h"



void EffectManager::AddEffect(EffectType type, float durationSeconds, float value) {
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


void EffectManager::Update(float dt) {
    // Aggiorno (decremento) il timer di tutti gli effetti
    for (auto& e : effects) {
        e.remainingTime -= dt;
    }


    // Rimuovo gli effetti scaduti
    effects.erase(
        std::remove_if(
            effects.begin(),
            effects.end(),
            [](const EffectInstance& e) { return e.remainingTime <= 0.0f; }
        ),
        effects.end()
    );

}


// Svuota il vettore degli effetti attivi
void EffectManager::ClearAllEffects() {
    effects.clear();
}

// Ritorna il numero di effetti attivi
int EffectManager::CountActiveEffects() const {
    return static_cast<int>(effects.size());
}

// Ritorna il moltiplicatore di velocità del player.
// Se non ci sono effetti Slow attivi -> 1.0 (velocità normale).
// Se ci sono più Slow -> viene applicato quello che rallenta di più.
float EffectManager::GetSpeedMultiplier() const {
    
    float multiplier = 1.0f;

    for (const auto& e : effects) {
        if (e.type == EffectType::Slow) {
            if(e.value < multiplier){
                multiplier = e.value;
            }
        }
    }

    return multiplier;
}