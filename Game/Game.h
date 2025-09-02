#pragma once
#include "Object.cpp"
#include "Child.cpp"
#include "Parent.cpp"
#include <functional>
#include <typeinfo>

class Scene
{
private:
    // The objects in the scene, if they are active they will be updated every frame
    std::list<Object *> objects;

public:
    // Constructor
    Scene(sf::Vector2f cameraSize, sf::Vector2f cameraCenter);

    // Deconstructor
    ~Scene();

    // Scene camera (defines what region is shown on screen)
    sf::View camera;

    // Returns a list with the objects in the scene
    std::list<Object *> GetObjects();
    // Add object to scene or if it's a child add it to its parent
    void AddObject(Object *o);
    // Remove object from scene
    void RemoveObject(Object *o);

    // Reacts to events, calls each active object's method
    void OnEvent(sf::Event event);

    // Updates every active Object
    void Update();

    // Draw every visble Object
    void Draw(sf::RenderWindow *window);
};

// Class that holds the properties for building a Scene
class SceneBuilder
{
private:
    // The resolution of the camera
    sf::Vector2f cameraSize;
    // The center point of the camera
    sf::Vector2f cameraCenter;

public:
    // Constructor
    SceneBuilder(sf::Vector2f cameraSize, sf::Vector2f cameraCenter, std::function<void(Scene *)> objects);

    // Creates and adds the specified objects to the created scene
    std::function<void(Scene *)> addObjectsToScene;

    // Returns the camera size
    sf::Vector2f GetCameraSize();

    // Returns the camera center
    sf::Vector2f GetCameraCenter();
};

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

    // Object that need to be deleted
    std::list<Object *> objectsToDelete;

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

    // Delete the object that are not used (object from the list)
    void DeleteObjects();

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
