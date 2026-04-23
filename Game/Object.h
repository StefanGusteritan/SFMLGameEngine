#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Class that represents a scene, it holds the objects in the scene and the camera
class Scene;

// Base Object class that all objects in the game will inherit from
// The object is a base instance of the game it has a position, rotation, scale
// Has an active state (if it's false the update function will not be called)
// Has a visible state (if it's false the draw function will not be called)
// Can be a parent of other objects that depend on it when it's deleted all its children are deleted
// Can be a child of another object its transform, visibility and active State are dependent of its parent's
class Object
{
private:
    // The scene that the object is in
    Scene *scene;

    // Name of the object (used for debugging)
    std::string name;
    // Layer of the object (objects with higher layers are drawn on top of objects with lower layers)
    int layer;

    // Active state of the object (if it's false the update function will not be called)
    bool active;
    // Visible state of the object (if it's false the draw function will not be called)
    bool visible;

    // Parent of the object (if it has one)
    Object *parent;
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

protected:
    //  Set the layer of the object
    void SetLayer(int newLayer);

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool activeState);
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Changes the local position of the Object
    void SetPosition(sf::Vector2f newPosition);
    // Moves the object from it's position in a direction with a specified speed
    void Move(sf::Vector2f direction, float speed);

    // Changes the local rotation of the Object
    void SetRotation(float newRotation);
    // Rotates the object form it's rotation twords an angle with a specified speed
    void Rotate(float angle, float speed);

    // Changes the local scale of the Object
    void SetScale(sf::Vector2f newScale);

public:
    // Constructor
    Object(Scene *scene);
    Object(Scene *scene, std::string name);
    Object(Scene *scene, Object *parent);
    Object(Scene *scene, std::string name, Object *parent);

    // Deconstructor
    virtual ~Object();

    std::string GetName();
    int GetLayer();

    // True if the object is active
    virtual bool IsActive();
    // True if the drawable object is visible (always true for not drawable object -to call the function for children-)
    virtual bool IsVisible();

    // Reacts to events
    virtual void OnEvent(sf::Event event);
    // Update the object each frame
    virtual void Update();
    // Draw the object (if it's drawable, else it does nothing)
    virtual void Draw(sf::RenderWindow &window);

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
    // Add a child to its list of children
    void AddChild(Object *c);
    // Remove a child from its list of children
    void RemoveChild(Object *c);

    // Return a list with the events that the object is subscribed to
    virtual const std::vector<sf::Event::EventType> GetEventsToSubscribe();

    // Mark the object to be deleted at the end of the frame
    void MarkToBeDeleted();
    // True if the object is marked to be deleted
    bool IsMarkedToBeDeleted();
};

// Object that has a sprite
class SpriteObject : public Object
{
protected:
    sf::Sprite sprite;

public:
    SpriteObject(Scene *scene);
    SpriteObject(Scene *scene, std::string name);
    SpriteObject(Scene *scene, Object *parent);
    SpriteObject(Scene *scene, std::string name, Object *parent);

    // Update object each frame add changes to the sprite
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;
};

// Object that has a text
class TextObject : public Object
{
protected:
    sf::Text text;

public:
    TextObject(Scene *scene);
    TextObject(Scene *scene, std::string name);
    TextObject(Scene *scene, Object *parent);
    TextObject(Scene *scene, std::string name, Object *parent);

    // Update object each frame add changes to the convex text
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;
};

// Object that has a circle shape
class CircleObject : public Object
{
protected:
    sf::CircleShape circle;

public:
    CircleObject(Scene *scene);
    CircleObject(Scene *scene, std::string name);
    CircleObject(Scene *scene, Object *parent);
    CircleObject(Scene *scene, std::string name, Object *parent);

    // Update object each frame add changes to the circle
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;
};

// Object that has a rectangle shape
class RectangleObject : public Object
{
protected:
    sf::RectangleShape rectangle;

public:
    RectangleObject(Scene *scene);
    RectangleObject(Scene *scene, std::string name);
    RectangleObject(Scene *scene, Object *parent);
    RectangleObject(Scene *scene, std::string name, Object *parent);

    // Update object each frame add changes to the rectangle
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;
};

// Object that has a convex shape
class ConvexObject : public Object
{
protected:
    sf::ConvexShape convexShape;

public:
    ConvexObject(Scene *scene);
    ConvexObject(Scene *scene, std::string name);
    ConvexObject(Scene *scene, Object *parent);
    ConvexObject(Scene *scene, std::string name, Object *parent);

    // Update object each frame add changes to the convex shape
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;
};
