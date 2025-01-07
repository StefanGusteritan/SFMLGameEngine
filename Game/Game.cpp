#include "Game.h"

Game::Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle)
{
    this->changingScene = false;
    this->mainWindow.create(windowSize, windowTitle, windowStyle);
    std::cout << "Game window created with title: " << windowTitle << std::endl;
}

Game::~Game()
{
    std::cout << "Game destroyed." << std::endl;
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
    // Get the new deltaTime
    this->UpdateDeltaTime();

    // Update the events
    this->UpdateEvents();

    // Verify the active scene
    if (!this->activeScene)
    {
        std::cout << "Failed to update scene objects (Null pointer to scene)" << std::endl;
        return;
    }

    // Update all active objects in the active scene
    this->activeScene->Update();

    // Update the view of the window
    this->mainWindow.setView(this->activeScene->camera);
}

void Game::Draw()
{
    this->mainWindow.clear();

    if (!this->activeScene)
    {
        std::cout << "Failed to draw scene objects (Null pointer to scene)" << std::endl;
        return;
    }

    this->activeScene->Draw(&this->mainWindow);
    this->mainWindow.display();
}

float Game::GetDeltaTime()
{
    return this->deltaTime;
}

Scene *Game::GetActiveScene()
{
    if (!this->activeScene)
    {
        std::cout << "Failed to get scene (Null pointer)" << std::endl;
        return NULL;
    }

    return this->activeScene;
}

void Game::ChangeScene()
{
    if (!nextScene)
    {
        std::cout << "Failed to set scene (Null pointer)" << std::endl;
        return;
    }

    Scene *previousScene = this->activeScene;
    this->activeScene = nextScene;

    this->changingScene = false;
    std::cout << "Active scene is set to " << nextScene << std::endl;

    if (!previousScene)
        std::cout << "Failed to delete previous scene (Null pointer)" << std::endl;
    else
        delete previousScene;
}

void Game::SetActiveScene(Scene *s)
{
    if (!s)
    {
        std::cout << "Failed to change scene (Null pointer)" << std::endl;
        return;
    }

    this->changingScene = true;
    this->nextScene = s;
}

void Game::Run()
{
    while (this->mainWindow.isOpen())
    {
        if (changingScene)
            ChangeScene();

        this->Update();
        this->Draw();
    }
}
