#include "TestGame.hpp"
#include "Scenes.hpp"

int main()
{
    game.SetActiveScene(playerScene);

    game.Run();

    return 0;
}