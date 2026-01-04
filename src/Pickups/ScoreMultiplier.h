#pragma once
#include "Pickup.h"


// ForwardDeclaration
class Character;
class EffectSystem;

// Classe che rappresenta l'effetto della moltiplicazione del punteggio del player per 10 sec.
class ScoreMultiplier : public Pickup{

    private:
        float scoreMultiplier;
        float durationSeconds;

    public:

        //Costruttore
        ScoreMultiplier(Vector2 pos, float radius, float scoreMultiplier, float durationSeconds);

        void Update(float dt) override;
        void Draw() const override;
        void OnCollect(Character& character,EffectSystem& effects) override;
        const char* GetCollectMessage() const override;


};