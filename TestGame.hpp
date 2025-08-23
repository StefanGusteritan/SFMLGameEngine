#pragma once
#include "Game/Game.cpp"
#include "Game/Scene.cpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

class TroopScene : public Scene
{
public:
    TroopScene();
};

class PlayerScene : public Scene
{
public:
    PlayerScene();
};