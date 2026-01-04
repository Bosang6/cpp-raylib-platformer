#pragma once
#include "raylib.h"
#include "Pickups/EffectSystem.h"

class UIStatusEffects
{

private:
    int marginX = 15;
    int startY = 45;

    static const char* EffectName(EffectSystem::EffectType t)
    {
        switch (t)
        {
            case EffectSystem::EffectType::Slow:            return "Slow";
            case EffectSystem::EffectType::ScoreMultiplier: return "MultiScore";
            default:                                       return "Effect";
        }
    }
    
public:
    // ancoraggio in alto a destra
    void SetAnchorTopRight(int marginX = 15, int startY = 45)
    {
        this->marginX = marginX;
        this->startY = startY;
    }

    void Draw(const EffectSystem& effects) const
    {
        auto active = effects.GetActiveEffects();
        if (active.empty()) return;

        int y = startY;
        int fontSize = 20;

        for (const auto& e : active)
        {
            const char* name = EffectName(e.type);

            // versione base: nome + tempo
            const char* line = TextFormat("%s: %.1fs", name, e.remainingTime);

            int w = MeasureText(line, fontSize);
            int x = GetScreenWidth() - w - marginX;

            DrawText(line, x, y + 1, fontSize, BLACK);
            DrawText(line, x, y,     fontSize, WHITE);

            y += 24;
        }
    }


};
