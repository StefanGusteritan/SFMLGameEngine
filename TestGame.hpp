#pragma once
#include "Game/Game.cpp"
#include "Game/Scene.cpp"

class Player;

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

extern SceneBuilder playerScene;
extern SceneBuilder troopScene;
extern SceneBuilder parentChildScene;