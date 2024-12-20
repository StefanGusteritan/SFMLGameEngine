#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <typeinfo>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Object
{
private:
    // Variables
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
    bool active;

protected:
    // Functions

    // Changes the position of the Object
    void SetPosition(sf::Vector2f newPosition);

    // Moves the object from it's position twords a direction with a specified speed
    void Move(sf::Vector2f direction, float speed);

    // Changes the rotation of the Object
    void SetRotation(float newRotation);

    // Rotates the object form it's rotation twords an angle with a specified speed
    void Rotate(float angle, float speed);

    // Changes the scale of the Object
    void SetScale(sf::Vector2f newScale);

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool a);

public:
    // Constructor
    Object();
    Object(bool activeState);

    // Deconstructor
    ~Object();
    // Actions that happen before the object is deleted (calls the deconstructor)
    virtual void Delete();

    // True if the object is active
    virtual bool IsActive();

    // Update the object each frame
    virtual void Update();

    // Get the position of the object
    sf::Vector2f GetPosition();

    // Get the rotation of the object
    float GetRotation();

    // Get the scale of the object
    sf::Vector2f GetScale();
};

// Object that is parent of other objects that depend on it when it's deleted all its children are deleted
class Parent : virtual public Object
{
private:
    std::list<Object *> children;

public:
    // Actions that happen before the object is deleted (calls the deconstructor)
    virtual void Delete() override;

    // Add a child to its list of children
    void AddChild(Object *c);

    // Remove a child from its list of children
    void RemoveChild(Object *c);
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

    // Moves the object from it's local position twords a direction with a specified speed
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

    // Actions that happen before the object is deleted (calls the deconstructor)
    virtual void Delete() override;

    // True if the object and its parent are active
    bool IsActive() override;

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

class VisibleObject : virtual public Object
{
private:
    bool visible;

protected:
    // Set the visibility of the object
    void SetVisible(bool visibility);

public:
    // Constructor
    VisibleObject();
    VisibleObject(bool activeState, bool visibility);

    // True if object is visible
    bool IsVisible();
};

// Object that has a sprite
class SpriteObject : public VisibleObject
{
protected:
    sf::Sprite sprite;

public:
    // Update object each frame add changes to the sprite
    virtual void Update() override;

    // Returns the sprite of the object so it can be drawn
    sf::Sprite GetSprite();
};

// Object that has a text
class TextObject : public VisibleObject
{
protected:
    sf::Text text;

public:
    // Update object each frame add changes to the convex text
    virtual void Update() override;

    // Returns the sprite of the object so it can be drawn
    sf::Text GetText();
};

// Object that has a circle shape
class CircleObject : public VisibleObject
{
protected:
    sf::CircleShape circle;

public:
    // Update object each frame add changes to the circle
    virtual void Update() override;

    // Returns the circle shape of the object so it can be drawn
    sf::CircleShape GetCircleShape();
};

// Object that has a rectangle shape
class RectangleObject : public VisibleObject
{
protected:
    sf::RectangleShape rectangle;

public:
    // Update object each frame add changes to the rectangle
    virtual void Update() override;

    // Returns the Rectangle Shape of the object so it can be drawn
    sf::RectangleShape GetRectangleShape();
};

// Object that has a convex shape
class ConvexObject : public VisibleObject
{
protected:
    sf::ConvexShape convexShape;

public:
    // Update object each frame add changes to the convex shape
    virtual void Update() override;

    // Returns the convex shape of the object so it can be drawn
    sf::ConvexShape GetConvexShape();
};
