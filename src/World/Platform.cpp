#include "Platform.h"
#include "raylib.h"

void Platform::Draw() const {
    DrawRectangleRounded((Rectangle){position.x, position.y, 80, 20}, 0.2f, 10, BLACK);
}