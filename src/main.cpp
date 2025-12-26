#include "raylib.h"
#include "Scene/Game.h"
int main()
{

    Game game;
    game.Start();
    //delete &game;

    CloseWindow();
    return 0;
}
