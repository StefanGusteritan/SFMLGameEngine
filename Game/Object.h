#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Base Object class that all objects in the game will inherit from
// The object is a base instance of the game it has a position, rotation, scale
// and an active state (if it's false the update function will not be called)
// Can be a parent of other objects that depend on it when it's deleted all its children are deleted
// Can be a child of another object its transform, visibility and active State are dependent of its parent's
class Object
{
private:
    // Parent of the object (if it has one)
    Object *parent;
    // True if the object has a parent
    bool hasParent;

    // Transform of the object
    // Global transform
    sf::Vector2f globalPosition;
    float globalRotation;
    sf::Vector2f globalScale;
    // Local transform
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;

    // Active state of the object (if it's false the update function will not be called)
    bool active;
    // Visible state of the object (if it's false the draw function will not be called)
    bool visible;

    // Children of the object
    std::list<Object *> children;

protected:
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

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool a);
    // Set the visibility of the object
    void SetVisible(bool visibility);

public:
    // Constructor
    Object();
    Object(Object *p);
    Object(bool activeState);
    Object(bool activeState, Object *p);
    Object(bool activeState, bool visibility);
    Object(bool activeState, bool visibility, Object *p);

    // Deconstructor
    virtual ~Object();

    // True if the object is active
    virtual bool IsActive();
    // True if the drawable object is visible (always true for not drawable object -to call the function for children-)
    virtual bool IsVisible();

    // Reacts to events
    virtual void OnEvent(sf::Event event);

    // Update the object each frame
    virtual void Update();
    // Draw the object (if it's drawable, else it does nothing)
    virtual void Draw(sf::RenderWindow *window);

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
    std::list<Object *> GetChildren();
    // Add a child to its list of children
    void AddChild(Object *c);
    // Remove a child from its list of children
    void RemoveChild(Object *c);
};

/*

// Object that is parent of other objects that depend on it when it's deleted all its children are deleted
class Parent : virtual public Object
{
private:
    std::list<Object *> children;

public:
    // Deconstructor
    virtual ~Parent();

    // Return a list with the children of th parent
    std::list<Object *> GetChildren();
    // Add a child to its list of children
    void AddChild(Object *c);
    // Remove a child from its list of children
    void RemoveChild(Object *c);

    // Reacts to events, calls each child's method
    virtual void OnEvent(sf::Event event) override;

    // Update Parent an Children each frame
    virtual void Update() override;

    // Draw Parent and Children (if drawable)
    virtual void Draw(sf::RenderWindow *window) override;
};

// Object that is a child of another object its transform, visibility and active State are dependent of its parent's
class Child : virtual public Object
{
private:
    Parent *parent;
    sf::Vector2f localPosition;
    float localRotation;
    sf::Vector2f localScale;

protected:
    // Changes the local position of the Object
    void SetLocalPosition(sf::Vector2f newPosition);
    // Moves the object from it's local position in a direction with a specified speed
    void LocalMove(sf::Vector2f direction, float speed);

    // Changes the local rotation of the Object
    void SetLocalRotation(float newRotation);
    // Rotates the object form it's local rotation twords an angle with a specified speed
    void LocalRotate(float angle, float speed);

    // Changes the local scale of the Object
    void SetLocalScale(sf::Vector2f newScale);

public:
    // Constructor
    Child(Parent *p);
    Child(bool activeState, Parent *p);

    // Deconstructor
    virtual ~Child();

    // Update the child object each frame
    virtual void Update() override;

    // Get the local position of the object
    sf::Vector2f GetLocalPosition();

    // Get the local rotation of the object
    float GetLocalRotation();

    // Get the local scale of the object
    sf::Vector2f GetLocalScale();

    // Get the parent of the object
    Parent *GetParent();
};

// Object that can be drawn on the window
class DrawableObject : virtual public Object
{
private:
    bool visible;

protected:
    // Set the visibility of the object
    void SetVisible(bool visibility);

public:
    // Constructor
    DrawableObject();
    DrawableObject(bool activeState, bool visibility);

    // Deconstructor
    virtual ~DrawableObject();

    // True if object is visible
    bool IsVisible() override;

    // Draw the object
    virtual void Draw(sf::RenderWindow *window) override;
};
*/
// Object that has a sprite
class SpriteObject : public Object
{
protected:
    sf::Sprite sprite;

public:
    SpriteObject();
    SpriteObject(Object *p);
    SpriteObject(bool activeState);
    SpriteObject(bool activeState, Object *p);
    SpriteObject(bool activeState, bool visibility);
    SpriteObject(bool activeState, bool visibility, Object *p);

    // Update object each frame add changes to the sprite
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow *window) override;
};

// Object that has a text
class TextObject : public Object
{
protected:
    sf::Text text;

public:
    TextObject();
    TextObject(Object *p);
    TextObject(bool activeState);
    TextObject(bool activeState, Object *p);
    TextObject(bool activeState, bool visibility);
    TextObject(bool activeState, bool visibility, Object *p);

    // Update object each frame add changes to the convex text
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow *window) override;
};

// Object that has a circle shape
class CircleObject : public Object
{
protected:
    sf::CircleShape circle;

public:
    CircleObject();
    CircleObject(Object *p);
    CircleObject(bool activeState);
    CircleObject(bool activeState, Object *p);
    CircleObject(bool activeState, bool visibility);
    CircleObject(bool activeState, bool visibility, Object *p);

    // Update object each frame add changes to the circle
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow *window) override;
};

// Object that has a rectangle shape
class RectangleObject : public Object
{
protected:
    sf::RectangleShape rectangle;

public:
    RectangleObject();
    RectangleObject(Object *p);
    RectangleObject(bool activeState);
    RectangleObject(bool activeState, Object *p);
    RectangleObject(bool activeState, bool visibility);
    RectangleObject(bool activeState, bool visibility, Object *p);

    // Update object each frame add changes to the rectangle
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow *window) override;
};

// Object that has a convex shape
class ConvexObject : public Object
{
protected:
    sf::ConvexShape convexShape;

public:
    ConvexObject();
    ConvexObject(Object *p);
    ConvexObject(bool activeState);
    ConvexObject(bool activeState, Object *p);
    ConvexObject(bool activeState, bool visibility);
    ConvexObject(bool activeState, bool visibility, Object *p);

    // Update object each frame add changes to the convex shape
    virtual void Update() override;

    // Draw the object
    void Draw(sf::RenderWindow *window) override;
};
