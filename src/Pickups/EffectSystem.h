#pragma once
#include <vector>
#include <algorithm>


// Classe responsabile della gestione degli effetti di pickup
class EffectSystem{

    public :
        // Enum che rappresenta i tipi di effetti disponibili nel gioco
        enum class EffectType {
            Slow,
            ScoreMultiplier
        };

        // read-only per UI
        struct ActiveEffectInfo {
            EffectType type;
            float remainingTime;
            float value;
        };


    private:
        // Struttura che rappresenta una singola istanza di effetto attivo
        struct EffectInstance {
            EffectType type;            
            float remainingTime;        
            float value;                
        };

        std::vector<EffectInstance> effects;            


    public:
        
        void AddEffect(EffectType type, float durationSeconds, float value);

        void Update(float dt);

        void ClearAllEffects();

        int CountActiveEffects() const;

        float GetSpeedMultiplier() const;
 
        float GetScoreMultiplier() const;
        
        // UI
        std::vector<ActiveEffectInfo> GetActiveEffects() const;
};