#pragma once
#include <iostream>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <typeinfo>

class Object
{
protected:
    // Variables
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
    bool active;

    // Functions

    // Changes the position of the Object
    void SetPosition(sf::Vector2f newPosition);

    // Changes the rotation of the Object
    void SetRotation(float newRotation);

    // Changes the scale of the Object
    void SetScale(sf::Vector2f newScale);

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

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool a);

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
class Parent : public Object
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
class Child : public Object
{
private:
    Parent *parent;

protected:
    sf::Vector2f localPosition;
    float localRotation;
    sf::Vector2f localScale;

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
};

// Object that has a sprite
class SpriteObject : public Object
{
protected:
    sf::Sprite sprite;
    bool visible;

public:
    // Constructor
    SpriteObject();
    SpriteObject(bool activeState, bool visibility);

    // Update object each frame add changes to the sprite
    virtual void Update() override;

    // True if object is visible
    bool IsVisible();
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Returns the sprite of the object so it can be drawn
    sf::Sprite GetSprite();
};

// Object that has a text
class TextObject : public Object
{
protected:
    sf::Text text;
    bool visible;

public:
    // Constructor
    TextObject();
    TextObject(bool activeState, bool visibility);

    // Update object each frame add changes to the convex text
    virtual void Update() override;

    // True if object is visible
    bool IsVisible();
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Returns the sprite of the object so it can be drawn
    sf::Text GetText();
};

// Object that has a circle shape
class CircleObject : public Object
{
protected:
    sf::CircleShape circle;
    bool visible;

public:
    // Constructor
    CircleObject();
    CircleObject(bool activeState, bool visibility);

    // Update object each frame add changes to the circle
    virtual void Update() override;

    // True if object is visible
    bool IsVisible();
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Returns the circle shape of the object so it can be drawn
    sf::CircleShape GetCircleShape();
};

// Object that has a rectangle shape
class RectangleObject : public Object
{
protected:
    sf::RectangleShape rectangle;
    bool visible;

public:
    // Constructor
    RectangleObject();
    RectangleObject(bool activeState, bool visibility);

    // Update object each frame add changes to the rectangle
    virtual void Update() override;

    // True if object is visible
    bool IsVisible();
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Returns the Rectangle Shape of the object so it can be drawn
    sf::RectangleShape GetRectangleShape();
};

// Object that has a convex shape
class ConvexObject : public Object
{
protected:
    sf::ConvexShape convexShape;
    bool visible;

public:
    // Constructor
    ConvexObject();
    ConvexObject(bool activeState, bool visibility);

    // Update object each frame add changes to the convex shape
    virtual void Update() override;

    // True if object is visible
    bool IsVisible();

    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Returns the convex shape of the object so it can be drawn
    sf::ConvexShape GetConvexShape();
};
