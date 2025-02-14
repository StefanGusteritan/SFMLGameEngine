#pragma once
#include "Game/Game.cpp"
#include "Game/Scene.cpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

class LevelScene : public Scene
{
public:
    LevelScene();
};