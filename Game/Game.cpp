#include "Game.h"

Game::Game(sf::VideoMode windowSize, char *windowTitle, sf::Uint32 windowStyle)
{
    this->mainWindow.create(windowSize, windowTitle, windowStyle);
}

Game::~Game()
{
}

void Game::UpdateDeltaTime()
{
    this->deltaTime = this->dtClock.getElapsedTime().asSeconds();
    dtClock.restart();
}

void Game::UpdateEvents()
{
    while (this->mainWindow.pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->mainWindow.close();
        }
    }
}

void Game::Update()
{
    this->UpdateDeltaTime();
    this->UpdateEvents();
}

void Game::Draw(sf::CircleShape s)
{
    this->mainWindow.clear();
    this->mainWindow.draw(s);
    this->mainWindow.display();
}

float Game::GetDeltaTime()
{
    return this->deltaTime;
}

void Game::Run(sf::CircleShape s)
{
    while (this->mainWindow.isOpen())
    {
        this->Update();
        this->Draw(s);
    }
}
