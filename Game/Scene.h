#pragma once
#include "Object.h"

// Class that represents a scene, it holds the objects in the scene and the camera
class Scene
{
private:
    // Name of the scene (Used for debugging)
    const std::string name;
    // The objects in the scene, if they are active they will be updated every frame
    std::map<int, std::vector<Object *>> layers;

    // Objects that need to be deleted
    std::vector<Object *> objectsToDelete;
    // Object that need to change parent
    std::vector<Object *> objectsToChangeParent;
    // Objects that need to be moved from a layer to another
    std::vector<Object *> objectsToMove;

    // Scene camera (defines what region is shown on screen)
    sf::View camera;

    // The objects that are subscribed to each event type
    std::unordered_map<sf::Event::EventType, std::vector<Object *>> eventSubscribers;

    // The collider objects in the scene
    std::vector<Object *> colliders;

    // Subscribe an object to the events that wants to react to
    void SubscribeToEvents(Object *o);
    // Unsubscribe an object from the events that it was subscribed to
    void UnsubscribeFromEvents(Object *o);

    // Add object to scene or if it's a child add it to its parent
    void AddObject(Object *o);
    // Remove object from scene
    void RemoveObject(Object *o);
    // Delete the object that are not used (object from the list)
    void DeleteObjects(bool removeFromScene = true);

    // Set an objects parent
    void SetObjectParent(Object *p, Object *o);
    // Change the parents of the objects marked
    void ChangeParents();

    // Set an objects layer
    void SetObjectLayer(int layer, Object *o);
    // Move the object marked to their new layers
    void MoveObjects();

    // Reacts to events, calls each active object's method
    void OnEvent(sf::Event event);

    // Updates every active Object
    void Update();

    // Draw every visble Object
    void Draw(sf::RenderWindow &window);

    // Get a list of the colliders that the target object intersects with
    // If called with onlySolid = true will get the collisions only with objects marked as solid
    void GetCollisions(Object *target, std::vector<Object *> &outCollisions, bool onlySolid);
    // Get a list of the colliders that the target rectangle intersects with
    // If called with onlySolid = true will get the collisions only with objects marked as solid
    // Returns true if there are collisions with objects that have the same bounds
    void GetCollisions(const sf::FloatRect target, Object *source, std::vector<Object *> &outCollisions, bool OnlySolid);

    friend class SceneManager;

public:
    // Constructor
    Scene(std::string name, sf::Vector2f cameraSize, sf::Vector2f cameraCenter);

    // Deconstructor
    ~Scene();

    // Return the name of the scene
    std::string GetName();
};

// Class that holds the properties for building a Scene
class SceneBuilder
{
private:
    // The name of the scene
    const std::string name;

    // The resolution of the camera
    const sf::Vector2f cameraSize;
    // The center point of the camera
    const sf::Vector2f cameraCenter;

public:
    // Constructor
    SceneBuilder(std::string name, sf::Vector2f cameraSize, sf::Vector2f cameraCenter, std::function<std::vector<Object *>()> objects);

    // Creates a vector of objects to be added to the created scene
    std::function<std::vector<Object *>()> objects;

    // Returns the scene name
    std::string GetName();

    // Returns the camera size
    sf::Vector2f GetCameraSize();

    // Returns the camera center
    sf::Vector2f GetCameraCenter();
};

// Class that manages the scenes of the game, it holds the active scene and the next scene to change to
class SceneManager
{
private:
    // The active scene that is being updated and drawn
    Scene *activeScene;
    // The next scene that will be active after the change scene process is triggered
    Scene *nextScene;
    // True if in the process of changing the scene
    bool changingScene;

    sf::View defaultCamera;

    // Change the active scene to the next scene and delete the previous scene
    void SetActiveScene();

    // Reacts to events from the active scene's objects
    void OnEvent(sf::Event event);
    // Update the active scene's objects
    void Update();
    // Draw the active scene's objects
    void Draw(sf::RenderWindow &window);

    // Delete the objects that are marked to be deleted
    void DeleteObjects();
    // Move the objects that are marled to be moved to their new parent
    void ChangeParents();
    // Move the objects that are marked to be moved to their new layer
    void MoveObjects();

    friend class Game;

public:
    // Constructor
    SceneManager();
    // Deconstructor
    ~SceneManager();

    // Set the next scene and trigger the change scene process
    void ChangeScene(SceneBuilder s);

    // Adds a new object in the active scene
    void AddObject(Object *o);
    // Remove objects from the scene and parent and add them to the list of Objects to Delete
    void RemoveObject(Object *o);

    // Set the parent of the object
    void SetObjectParent(Object *p, Object *o);

    // Sets the layer of the specified object
    void SetObjectLayer(int layer, Object *o);

    // Get a list of the colliders that the target object intersects with
    // If called with onlySolid = true will get the collisions only with objects marked as solid
    void GetCollisions(Object *target, std::vector<Object *> &outCollisions, bool onlySolid = false);
    // Get a list of the colliders that the target rectangle intersects with
    // If called with onlySolid = true will get the collisions only with objects marked as solid
    // Returns true if there are collisions with objects that have the same bounds
    void GetCollisions(const sf::FloatRect target, Object *source, std::vector<Object *> &outCollisions, bool onlySolid = false);

    // Get a pointer to the camera of the active scene
    sf::View &GetCamera();
};