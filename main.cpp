#include "Game\Game.cpp"

int main()
{
    Game test(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    test.Run(shape);

    return 0;
}