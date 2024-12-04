#include "Game.h"

Game::Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle)
{
    this->mainWindow.create(windowSize, windowTitle, windowStyle);
    std::cout << "Game window created with title: " << windowTitle << std::endl;
}

Game::~Game()
{
    std::cout << "Game object destroyed." << std::endl;
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

void Game::Draw()
{
    this->mainWindow.clear();
    this->mainWindow.display();
}

float Game::GetDeltaTime()
{
    return this->deltaTime;
}

void Game::Run()
{
    while (this->mainWindow.isOpen())
    {
        this->Update();
        this->Draw();
    }
}
