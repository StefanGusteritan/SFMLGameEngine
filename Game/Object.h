#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Object
{
protected:
    // Variables
    sf::Sprite sprite;
    sf::Vector2f localPosition;
    float localRotation;
    sf::Vector2f localScale;
    bool active;
    bool visible;

    // Functions

    // Changes the local position of the Object
    void SetPosition(sf::Vector2f newPosition);

    // Changes the local rotation of the Object
    void SetRotation(float newRotation);

    // Changes the local scale of the Object
    void SetScale(sf::Vector2f newScale);

public:
    // Constructor
    Object();
    Object(bool activeState, bool visibility);

    // Deconstructor
    ~Object();

    // True if the object is active
    virtual bool IsActive();

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool a);

    // Update the object each frame
    virtual void Update();

    // True if the object is visible
    virtual bool IsVisible();

    // Set the visiblity (if it's false the draw function will not be called)
    void SetVisible(bool v);

    // Get the position of the object
    sf::Vector2f GetPosition();

    // Get the rotation of the object
    float GetRotation();

    // Get the scale of the object
    sf::Vector2f GetScale();

    // Get the origin of the object
    sf::Vector2f GetOrigin();
};

// Object that is a child of another object its transform, visibility and active State are dependent of its parent's
class Child : Object
{
private:
    Object *parent;

public:
    // Constructor
    Child(bool activeState, bool visibility, Object *p);

    // True if the object and its parent are active
    bool IsActive();

    // Update the child object each frame
    virtual void Update();

    // True if the object and its parent are visible
    bool IsVisible();
};
