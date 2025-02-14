#include "TestGame.hpp"
#include "Troop.hpp"

LevelScene::LevelScene() : Scene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540))
{
    this->AddObject(new Troop);
}