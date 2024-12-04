#pragma once
#include "Game/Object.cpp"
#include "Game/Child.cpp"
#include "Game/Parent.cpp"
#include <typeinfo>

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

class Scene
{
private:
    // The objects in the scene, if they are active they will be updated every frame
    std::list<Object> objects;

public:
    // Constructor
    Scene();

    // Deconstructor
    ~Scene();

    // Add object to scene
    void AddObject(Object *o);

    // Remove object from scene
    void RemoveObject(Object *o);

    // Updates every active Object
    void Update();

    // Draw every visble Object
    void Draw();
};
