#pragma once
#include <string>
#include <deque>

#include "raylib.h"

// Mostra a schermo i messaggi dei Pickup
class UIPickMessage
{
    private:

        struct Message
        {
            std::string text;
            float duration = 1.2f;
            float timeLeft = 1.2f;

            bool useCustomPos = false;
            Vector2 pos = {0,0};
        };

        std::vector<Message> messages;
        int topY = 18;


    public:

        void PushAt(const char* text, Vector2 screenPos, float durationSeconds = 1.2f)
        {
            if (!text || text[0] == '\0') return;

            Message m;
            m.text = text;
            m.duration = durationSeconds;
            m.timeLeft = durationSeconds;
            m.useCustomPos = true;
            m.pos = screenPos;

            messages.push_back(std::move(m));
            
        }


        void Update(float dt)
        {
            if (messages.empty()) return;

            for (auto& m : messages)
                m.timeLeft -= dt;

            messages.erase(
                std::remove_if(messages.begin(), messages.end(),
                    [](const Message& m) { return m.timeLeft <= 0.0f; }),
                messages.end()
            );
        }


        void Draw() const
        {
            if (messages.empty()) return;

            const int baseFontSize = 32;

            for (const Message& m : messages)
            {
                float t = (m.duration > 0.0f) ? (m.timeLeft / m.duration) : 0.0f;
                
                float alpha = t;

                float scale = 0.6f + 0.4f * t;
                int fontSize = (int)(baseFontSize * scale);

                int textWidth = MeasureText(m.text.c_str(), fontSize);

                int x, y;

                if (m.useCustomPos)
                {
                    x = (int)(m.pos.x - textWidth * 0.5f);
                    y = (int)(m.pos.y);
                }
                else
                {
                    // se usi la modalità vecchia "in alto", impilali verticalmente
                    x = GetScreenWidth() / 2 - textWidth / 2;
                    y = topY;
                }

                // Effetto salita
                float rise = (1.0f - t) * 25.0f;

                DrawText(m.text.c_str(), x, (int)(y - rise), fontSize, Fade(WHITE, alpha));
            }
        }

    void SetTopY(int y) { topY = y; }
};
