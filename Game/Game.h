#pragma once
#include "Object.cpp"
#include "Child.cpp"
#include "Parent.cpp"

class Scene
{
private:
    // The objects in the scene, if they are active they will be updated every frame
    std::list<Object *> objects;

public:
    // Scene camera (defines what region is shown on screen)
    sf::View camera;

    // Constructor
    Scene(sf::Vector2f cameraSize, sf::Vector2f cameraCenter);

    // Deconstructor
    ~Scene();

    // Add object to scene
    void AddObject(Object *o);

    // Remove object from scene
    void RemoveObject(Object *o);

    // Updates every active Object
    void Update();

    // Draw every visble Object
    void Draw(sf::RenderWindow *window);
};

class Game
{
private:
    // Variables
    sf::RenderWindow mainWindow;

    Scene *activeScene;

    sf::Clock dtClock;
    float deltaTime;

    sf::Event event;

    // True if in the process of changing the scene
    bool changingScene;
    // The next scene that will be active
    Scene *nextScene;

    // Functions

    // Update the deltaTime
    void UpdateDeltaTime();

    // Gets and reacts to events
    void UpdateEvents();

    // Update the frame
    void Update();

    // Render the frame
    void Draw();

    // Trigger the change scene process
    void ChangeScene();

public:
    // Constructor - Initiates the game window
    Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle);

    // Deconstructor
    ~Game();

    // Get the deltaTime
    float GetDeltaTime();

    // Get the active scene
    Scene *GetActiveScene();

    // Set the active scene
    void SetActiveScene(Scene *s);

    // Get a pointer to the window
    sf::WindowBase *GetWindow();

    // Open the game window and run the game
    void Run();
};
