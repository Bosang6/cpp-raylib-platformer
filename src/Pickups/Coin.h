#pragma once
#include "Pickup.h"



// Classe che rappresenta una moneta nel gioco
class Coin : public Pickup {
    
    private:
        float angle{0.0f};              // Angolo per l'animazione di rotazione
        float spinSpeed{4.0f};          // Velocità di rotazione
        float minSpinScale{0.2f};
        int value;                   // Valore della moneta


    public:

        // Costruttore della moneta
        Coin(Vector2 pos, float radius, int value);


        // Metodo per aggiornare lo stato della moneta (es. animazioni)
        void Update(float dt) override;

        
        // Metodo per disegnare la moneta
        void Draw() const override;


        // Cosa succede quando viene raccolto
        void OnCollect(Character& character, EffectSystem& effects) override;

        
        int GetValue() const {return value;}


    private:

        float GetSpinScaleX() const;

};