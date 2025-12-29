#pragma once
#include <vector>
#include <algorithm>


// Classe responsabile della gestione degli effetti di pickup
class EffectSystem{

    public :
        // Enum che rappresenta i tipi di effetti disponibili nel gioco
        // Slow : rallenta il giocatore
        enum class EffectType {
            Slow,
            ScoreMultiplier
        };


    private:
        // Struttura che rappresenta una singola istanza di effetto attivo
        struct EffectInstance {
            EffectType type;            // Tipo di effetto
            float remainingTime;        // Tempo rimanente per l'effetto
            float value;                // Valore associato all'effetto (es. 0.5 per slow) 
        };

        std::vector<EffectInstance> effects;            // Vettore che contiene tutti gli effetti attivi


    public:
        // Aggiunge un effetto: se già presente, aggiorna il timer ed il valore
        void AddEffect(EffectType type, float durationSeconds, float value = 1.0f);

        // Aggiorna il timer di tutti gli effetti attivi e rimuove quelli scaduti
        void Update(float dt);

        // Rimuove tutti gli effetti attivi
        void ClearAllEffects();

        // Conta quanti effetti sono attivi
        int CountActiveEffects() const;

        // Getter : moltiplicatore di velocità in base agli effetti attivi (default 1.0f)
        float GetSpeedMultiplier() const;

        // Getter : moltiplicatore di punteggio 
        float GetScoreMultiplier() const;

        // In futuro aggiungere ScoreMultiplier e ReverseControls
};