#pragma once
#include "Scene.h"

class Game
{
private:
    // Variables

    // Window
    sf::RenderWindow mainWindow;

    // Delta Time
    sf::Clock dtClock;
    float deltaTime;

    // Events
    sf::Event event;

    // Scene
    Scene *activeScene = nullptr;
    // The next scene that will be active
    Scene *nextScene = nullptr;
    // True if in the process of changing the scene
    bool changingScene;

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

    // Get a pointer to the main window of the game
    sf::WindowBase *GetWindow();

    // Get the deltaTime
    float GetDeltaTime();

    // Get a pointer to the camera of the active scene
    sf::View *GetSceneCamera();

    // Set the active scene
    void SetActiveScene(SceneBuilder s);

    // Adds a new object in the active scene
    void AddObject(Object *o);
    // Remove objects from the scene and parent and add them to the list of Objects to Delete
    void RemoveObject(Object *o);

    // Open the game window and run the game
    void Run();
};
