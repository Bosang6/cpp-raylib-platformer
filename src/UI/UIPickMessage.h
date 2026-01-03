#pragma once
#include <string>
#include <deque>
#include "raylib.h"


// Classe per gestire la stampa a schermo quando si raccolgono i Pickups
class UIPickMessage{

    private:
        struct Message{
            std::string text;
            float timeLeft{0.0f};
            float duration{0.0f};
        };

        std::deque<Message> messages;

    public: 

        // Aggiunge un messaggio al centro dello schermo
        void Push(const std::string& text, float duration = 1.2f){
            Message m;
            m.text = text;
            m.duration = duration;
            m.timeLeft = duration;
            messages.push_back(std::move(m));
        }

        // Aggiorna il timer del mesaggio
        void Update(float dt){
            if(messages.empty()) { return; }

            messages.front().timeLeft -= dt;
            if(messages.front().timeLeft <= 0.0f){
                messages.pop_front();
            }
        }


        void Draw() const{
            if(messages.empty()) { return; }

            const Message& m = messages.front();

            // Fade-out negli ultimi 30%
            float t = m.timeLeft / m.duration;
            float alpha = (t < 0.3f) ? ( t / 0.3f) : 1.0f;

            int fontSize = 32;
            int w = MeasureText(m.text.c_str(), fontSize);

            int x = GetScreenWidth() /2 - w /2;
            int y = GetScreenHeight() /2 - fontSize /2;

            DrawText(m.text.c_str(), x, y, fontSize, Fade(BLACK, alpha));
        }

};