#pragma once
#include "Game\Game.cpp"
#include "Game\Scene.cpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

float s1State = 0, s2State = 0;

class Scene1 : public Scene
{
public:
    Scene1();
};

class Scene2 : public Scene
{
public:
    Scene2();
};