#pragma once
#include "TimeManager.h"
#include "Scene.h"

class Game
{
private:
    // Window of the game
    sf::RenderWindow mainWindow;

    // Events
    sf::Event event;

    // Gets and reacts to events
    void UpdateEvents();

    // Update the frame
    void Update();

    // Render the frame
    void Draw();

public:
    // Constructor - Initiates the game window
    Game(sf::VideoMode windowSize, const std::string windowTitle, sf::Uint32 windowStyle);

    // Deconstructor
    ~Game();

    // Time manager, used to get the delta time
    TimeManager time;

    // Scene manager, used to manage the active scene and the change scene process
    SceneManager sceneManager;

    // Get a reference to the main window of the game
    const sf::RenderWindow &GetWindow();

    // Open the game window and run the game
    void Run();
};
