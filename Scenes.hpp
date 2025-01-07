#include "TestGame.hpp"
#include "TestObj.hpp"

Scene1::Scene1() : Scene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540))
{
    this->AddObject(new TestObj);
}

Scene2::Scene2() : Scene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540))
{
    this->AddObject(new TestObjSquare);
}