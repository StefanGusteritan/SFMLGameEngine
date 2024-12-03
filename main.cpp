#include "Game\Game.cpp"

int main()
{
    Game test(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

    test.Run();

    return 0;
}