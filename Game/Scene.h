#pragma once
#include "Object.h"
#include <functional>

class Scene
{
private:
    // The objects in the scene, if they are active they will be updated every frame
    std::list<Object *> objects;

    // Object that need to be deleted
    std::list<Object *> objectsToDelete;

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
    // Delete the object that are not used (object from the list)
    void DeleteObjects(bool removeFromScene = true);

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