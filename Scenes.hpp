#pragma once
#include "TestGame.hpp"
#include "Troop.hpp"
#include "Player.hpp"

TroopScene::TroopScene() : Scene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540))
{
    this->AddObject(new Troop);
}

PlayerScene::PlayerScene() : Scene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540))
{
    this->AddObject(new Player);
}