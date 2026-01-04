#pragma once
#include <string>
#include <deque>
#include "raylib.h"

class UIPickMessage
{


private:
    struct Message
    {
        std::string text;
        float duration = 1.2f;
        float timeLeft = 1.2f;
    };

    std::deque<Message> messages;
    int topY = 18;
    int maxQueue = 3;


public:
    // durata di default per i messaggi
    void Push(const char* text, float durationSeconds = 1.2f)
    {
        if (!text || text[0] == '\0') return;

        Message m;
        m.text = text;
        m.duration = durationSeconds;
        m.timeLeft = durationSeconds;

        messages.push_back(m);

        // opzionale: limita la coda
        while ((int)messages.size() > maxQueue)
            messages.pop_front();
    }

    void Update(float dt)
    {
        if (messages.empty()) return;

        Message& m = messages.front();
        m.timeLeft -= dt;

        if (m.timeLeft <= 0.0f)
            messages.pop_front();
    }

    void Draw() const
    {
        if (messages.empty()) return;

        const Message& m = messages.front();

        float t = (m.duration > 0.0f) ? (m.timeLeft / m.duration) : 0.0f;
        float alpha = (t < 0.3f) ? (t / 0.3f) : 1.0f; // fade out ultimi 30%

        int fontSize = 32;
        int textWidth = MeasureText(m.text.c_str(), fontSize);

        int x = GetScreenWidth() / 2 - textWidth / 2;
        int y = topY;

        
        DrawText(m.text.c_str(), x, y, fontSize, WHITE);
    }

    void SetTopY(int y) { topY = y; }



};
