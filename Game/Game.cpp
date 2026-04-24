#include "Game.h"

Game::Game(sf::VideoMode windowSize, const std::string windowTitle, sf::Uint32 windowStyle)
{
    this->mainWindow.create(windowSize, windowTitle, windowStyle);
    std::cout << "Created: Game" << std::endl;
    std::cout << "Created: Window with title: " << windowTitle << std::endl;
}

Game::~Game()
{
    std::cout << "Deleted: Game" << std::endl;
}

const sf::RenderWindow &Game::GetWindow()
{
    return this->mainWindow;
}

void Game::UpdateEvents()
{
    while (this->mainWindow.pollEvent(this->event))
    {
        // Update the events from the active scene's objects
        this->sceneManager.OnEvent(this->event);

        // Close event
        if (this->event.type == sf::Event::Closed)
            this->mainWindow.close();
    }
}

void Game::Update()
{
    // Get the new deltaTime
    this->time.UpdateDeltaTime();

    // Update the events
    this->UpdateEvents();

    // Update the active scene objects
    this->sceneManager.Update();
}

void Game::Draw()
{
    // Clears the last frame
    this->mainWindow.clear();

    // Draw the active scene objects
    this->sceneManager.Draw(this->mainWindow);

    // Display the frame
    this->mainWindow.display();
}

void Game::Run()
{
    // Main game loop
    while (this->mainWindow.isOpen())
    {
        // If the scene is scheduled to change, change the scene
        this->sceneManager.SetActiveScene();

        // Delete the objects that are marked to be deleted in the active scene
        this->sceneManager.DeleteObjects();
        // Move the objects that are marked to be deleted in the active scene
        this->sceneManager.MoveObjects();

        // Update and draw the frame
        this->Update();
        this->Draw();
    }
}