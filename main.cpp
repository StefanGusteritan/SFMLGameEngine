#include "Scenes.hpp"

int main()
{
    game.SetActiveScene(new PlayerScene);

    game.Run();

    return 0;
}