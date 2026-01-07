#pragma once
#include "Pickup.h"



// Classe che rappresenta una moneta nel gioco
class Coin : public Pickup {
    
    private:
        // Rotazione 
        float angle{0.0f};              
        float spinSpeed{4.0f};          
        float minSpinScale{0.2f};
        
        // Valore
        int value;                  

        // Gestione dello sprite 
        static Texture2D spriteSheet;
        static bool textureLoaded;
        static int instanceCount;
        
        // Animazione sprite
        Rectangle currentFrame;
        int frameIndex;
        float frameTime;
        float drawScale{2.0f};

    public:

        Coin(Vector2 pos, float radius, int value);
        ~Coin();

        void Update(float dt) override;

        void Draw() const override;

        void OnCollect(Character& character, EffectSystem& effects) override;
        
        int GetValue() const {return value;}


    private:

        float GetSpinScaleX() const;
        static void LoadSpriteSheet();
        static void UnloadSpriteSheet();

        
};