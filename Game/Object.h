#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Base Object class that all objects in the game will inherit from
// The object is a base instance of the game it has a position, rotation, scale
// Has an active state (if it's false the update function will not be called)
// Has a visible state (if it's false the draw function will not be called)
// Can be a parent of other objects that depend on it when it's deleted all its children are deleted
// Can be a child of another object its transform, visibility and active State are dependent of its parent's
class Object
{
private:
    // Name of the object (used for debugging)
    const std::string name;
    // Layer of the object (objects with higher layers are drawn on top of objects with lower layers)
    int layer;
    // layer that the object will move to
    int newLayer;

    // True when the object is completely added to the scene
    bool registered;
    // The index of the object in the layer or in its parent's children list
    size_t objectIndex;
    // The index of the object in the event's subscribers list of the events that is subscribed to
    std::unordered_map<sf::Event::EventType, size_t> subscriberIndices;

    // Active state of the object (if it's false the update function will not be called)
    bool active;
    // Visible state of the object (if it's false the draw function will not be called)
    bool visible;

    // Parent of the object (if it has one)
    Object *parent;
    // Parent that the object will move to
    Object *newParent;
    // True if the object has a parent
    bool hasParent;

    // Children of the object
    std::vector<Object *> children;

    // Transform of the object
    // Global transform
    sf::Vector2f globalPosition;
    float globalRotation;
    sf::Vector2f globalScale;
    // Local transform
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;

    // True if the object is marked to be deleted (if it's true the object will be deleted at the end of the frame)
    bool toBeDeleted;
    // True if the object is marked to change its parent (if it's true the object will change it's parent at the end of the frame)
    bool toChangeParent;
    // True if the object is marked to be moved to other layer (if it's true the object will be moved at the end of the frame)
    bool toBeMoved;

    // Add a child to its list of children (Should only be called from Scene class )
    void AddChild(Object *c);
    // Remove a child from its list of children (Should only be called from Scene class)
    void RemoveChild(Object *c);

    friend class Scene;

protected:
    // Reacts to events (Should be called only from Scene class)
    virtual void OnEvent(sf::Event event);
    // Update the object each frame (Should be called only from Scene class)
    virtual void Update();
    // Draw the object (Should be called only from Scene class)
    virtual void Draw(sf::RenderWindow &window);

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool activeState);
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Changes the local position of the Object
    void SetPosition(sf::Vector2f newPosition);
    // Moves the object from it's position in a direction with a specified speed
    // dt - "Delta time" the time it took the last frame to get processed and rendered
    // Used for conversion to pixel-per-second to pixel-per frame
    void Move(sf::Vector2f direction, float speed, float dt);

    // Changes the local rotation of the Object
    void SetRotation(float newRotation);
    // Rotates the object form it's rotation twords an angle with a specified speed
    // dt - "Delta time" the time it took the last frame to get processed and rendered
    // Used for conversion to pixel-per-second to pixel-per frame
    void Rotate(float angle, float speed, float dt);
    // Changes the local scale of the Object
    void SetScale(sf::Vector2f newScale);

public:
    // Constructor
    Object();
    Object(std::string name);
    Object(int layer);
    Object(Object *parent);
    Object(std::string name, int layer);
    Object(std::string name, Object *parent);
    Object(int layer, Object *parent);
    Object(std::string name, int layer, Object *parent);

    // Deconstructor
    virtual ~Object();

    //  Get the name of the object
    std::string GetName();

    // Get the layer the object is on
    int GetLayer();

    // True if the object is registered and exists in a scene
    bool IsRegistered();

    // True if the object is active
    bool IsActive();
    // True if the drawable object is visible (always true for not drawable object -to call the function for children-)
    bool IsVisible();

    // Get the global position of the object
    sf::Vector2f GetGlobalPosition();
    // Get the global rotation of the object
    float GetGlobalRotation();
    // Get the global scale of the object
    sf::Vector2f GetGlobalScale();
    // Get the local position of the object
    sf::Vector2f GetPosition();
    // Get the local rotation of the object
    float GetRotation();
    // Get the local scale of the object
    sf::Vector2f GetScale();

    // True if the object is a child of another object
    bool IsChild();
    // Get the parent of the object
    Object *GetParent();
    // Return a list with the children of th parent
    const std::vector<Object *> &GetChildren();

    // Return a list of objects that are supposed to be added as children when the object is registered
    virtual const std::vector<Object *> GetChildrenToAdd();

    // Return a list with the events that the object is subscribed to
    virtual const std::vector<sf::Event::EventType> GetEventsToSubscribe();

    // True if the object is marked to be deleted
    bool IsMarkedToBeDeleted();
    // True if the object is  marked to change its parent
    bool IsMarkedToChangeParent();
    // True if the object is marked to be moved
    bool IsMarkedToBeMoved();
};

// Object that has a sprite
class SpriteObject : public Object
{
private:
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    sf::Sprite sprite;

    // Update object each frame add changes to the sprite
    virtual void Update() override;

public:
    SpriteObject();
    SpriteObject(std::string name);
    SpriteObject(int layer);
    SpriteObject(Object *parent);
    SpriteObject(std::string name, int layer);
    SpriteObject(std::string name, Object *parent);
    SpriteObject(int layer, Object *parent);
    SpriteObject(std::string name, int layer, Object *parent);
};

// Object that has a text
class TextObject : public Object
{
private:
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    sf::Text text;

    // Update object each frame add changes to the convex text
    virtual void Update() override;

public:
    TextObject();
    TextObject(std::string name);
    TextObject(int layer);
    TextObject(Object *parent);
    TextObject(std::string name, int layer);
    TextObject(std::string name, Object *parent);
    TextObject(int layer, Object *parent);
    TextObject(std::string name, int layer, Object *parent);
};

// Object that has a circle shape
class CircleObject : public Object
{
private:
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    sf::CircleShape circle;

    // Update object each frame add changes to the circle
    virtual void Update() override;

public:
    CircleObject();
    CircleObject(std::string name);
    CircleObject(int layer);
    CircleObject(Object *parent);
    CircleObject(std::string name, int layer);
    CircleObject(std::string name, Object *parent);
    CircleObject(int layer, Object *parent);
    CircleObject(std::string name, int layer, Object *parent);
};

// Object that has a rectangle shape
class RectangleObject : public Object
{
private:
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    sf::RectangleShape rectangle;

    // Update object each frame add changes to the rectangle
    virtual void Update() override;

public:
    RectangleObject();
    RectangleObject(std::string name);
    RectangleObject(int layer);
    RectangleObject(Object *parent);
    RectangleObject(std::string name, int layer);
    RectangleObject(std::string name, Object *parent);
    RectangleObject(int layer, Object *parent);
    RectangleObject(std::string name, int layer, Object *parent);
};

// Object that has a convex shape
class ConvexObject : public Object
{
private:
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    sf::ConvexShape convexShape;

    // Update object each frame add changes to the convex shape
    virtual void Update() override;

public:
    ConvexObject();
    ConvexObject(std::string name);
    ConvexObject(int layer);
    ConvexObject(Object *parent);
    ConvexObject(std::string name, int layer);
    ConvexObject(std::string name, Object *parent);
    ConvexObject(int layer, Object *parent);
    ConvexObject(std::string name, int layer, Object *parent);
};
