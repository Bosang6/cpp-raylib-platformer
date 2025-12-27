#pragma once
#include "Pickup.h"


// Classe che rappresenta una moneta nel gioco
class Coin : public Pickup {
    
    private:
        float angle{0.0f};              // Angolo per l'animazione di rotazione
        float spinSpeed{4.0f};          // Velocità di rotazione
        int value{1};                   // Valore della moneta

    public:

        // Costruttore della moneta
        Coin(Vector2 pos, float radius = 10.f, int v = 1);


        // Metodo per aggiornare lo stato della moneta (es. animazioni)
        void Update(float dt) override;

        
        // Metodo per disegnare la moneta
        void Draw() const override;


        // Cosa succede quando viene raccolto
        void OnCollect(Character& character, EffectManager& effects) override;

};