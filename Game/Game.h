#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
    // Variables
    sf::RenderWindow mainWindow;

    sf::Clock dtClock;
    float deltaTime;

    sf::Event event;

    sf::CircleShape shape;

    // Functions

    // Update the deltaTime
    void UpdateDeltaTime();

    // Gets and reacts to events
    void UpdateEvents();

    // Update the frame
    void Update();

    // Render the frame
    void Draw();

public:
    // Constructor - Initiates the game window
    Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle);

    // Deconstructor
    ~Game();

    // Get the deltaTime
    float GetDeltaTime();

    // Open the game window and run the game
    void Run();
};
