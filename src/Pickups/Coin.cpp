#include "Coin.h"
#include "raylib.h"
#include "cmath"

// Se mi servirà usare Character.AddScore
// #include "Character/Character.h"


// Costruttore della moneta
Coin::Coin(Vector2 pos, float radius, int v)
    : Pickup(pos, radius), value(v) {}


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
    // Valore che oscilla tra 0.6 e 1.0 (effetto rotazione)
    float brightness = 0.6f + 0.4f * std::fabs(std::cos(angle));

    // Cerchio principale della moneta
    DrawCircleV(position, radius, Fade(GOLD, brightness));

    // Bordo della moneta
    DrawCircleLines(
        (int)position.x,
        (int)position.y,
        radius,
        ORANGE
    );
}


// Cosa succede quando viene raccolto
// Aggiunge il valore della moneta al punteggio del giocatore
void Coin::OnCollect(Character& character, EffectManager&) {
    collected = true;
    //character.AddScore(value);
}





