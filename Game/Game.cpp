#include "Game.h"

Game::Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle)
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

    // Debug
    std::cout << "Delta Time: " << this->deltaTime << std::endl
              << "Frame Rate: " << 1 / this->deltaTime << std::endl
              << "Window Size: " << this->mainWindow.getSize().x << 'x' << this->mainWindow.getSize().y
              << "\033[A\033[A\r";
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
