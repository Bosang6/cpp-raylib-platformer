#include "Coin.h"
#include "raylib.h"
#include "cmath"

// Se mi servirà usare Character.AddScore
// #include "Character/Character.h"


// Costruttore della moneta
Coin::Coin(Vector2 pos, float radius, int value)
    : Pickup(pos, radius), value(value) {}


// Metodo per aggiornare lo stato della moneta (es. animazioni)
void Coin::Update(float dt) {
    // Aggiorno l'angolo per l'animazione di rotazione
    angle += spinSpeed * dt;

    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }
}    


// Metodo per disegnare la moneta
void Coin::Draw() const {
    
    float bob = sin(animTime * 4.0f) * 5.0f;

    Vector2 drawPos = {
        position.x,
        position.y + bob
    };

    DrawCircleV(drawPos, radius, GOLD);
    DrawCircleLines(drawPos.x, drawPos.y, radius, ORANGE);
}


// Cosa succede quando viene raccolto
// Aggiunge il valore della moneta al punteggio del giocatore
void Coin::OnCollect(Character& character, EffectSystem& effects) {
    collected = true;
    //character.AddScore(value, effects);
}





