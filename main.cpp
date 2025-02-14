#include "Scenes.hpp"

int main()
{
    game.SetActiveScene(new LevelScene);

    game.Run();

    return 0;
}