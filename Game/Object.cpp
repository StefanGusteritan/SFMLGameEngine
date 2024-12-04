#include "Object.h"

void Object::SetPosition(sf::Vector2f newPosition)
{
    this->position = newPosition;
}

void Object::SetRotation(float newRotation)
{
    this->rotation = newRotation;
}

void Object::SetScale(sf::Vector2f newScale)
{
    this->scale = newScale;
}

Object::Object()
{
    this->active = true;

    // Initialize transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << std::endl;
}

Object::Object(bool activeState)
{
    this->active = activeState;

    // Initialize transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << std::endl;
}

Object::~Object()
{
    std::cout << "Object destroyed: " << this << std::endl;
}

bool Object::IsActive()
{
    return this->active;
}

void Object::SetActive(bool a)
{
    this->active = a;
}

void Object::Update()
{
}

sf::Vector2f Object::GetPosition()
{
    return this->position;
}

float Object::GetRotation()
{
    return this->rotation;
}

sf::Vector2f Object::GetScale()
{
    return this->scale;
}

SpriteObject::SpriteObject()
{
    this->visible = true;
    this->Object::Object();
}

SpriteObject::SpriteObject(bool activeState, bool visibility)
{
    this->visible = visibility;
    this->Object::Object(activeState);
}

void SpriteObject::Update()
{
    this->sprite.setPosition(this->position);
    this->sprite.setRotation(this->rotation);
    this->sprite.setScale(this->scale);
}

TextObject::TextObject()
{
    this->visible = true;
    this->Object::Object();
}

TextObject::TextObject(bool activeState, bool visibility)
{
    this->visible = visibility;
    this->Object::Object(activeState);
}

void TextObject::Update()
{
    this->text.setPosition(this->position);
    this->text.setRotation(this->rotation);
    this->text.setScale(this->scale);
}

CircleObject::CircleObject()
{
    this->visible = true;
    this->Object::Object();
}

CircleObject::CircleObject(bool activeState, bool visibility)
{
    this->visible = visibility;
    this->Object::Object(activeState);
}

void CircleObject::Update()
{
    this->circle.setPosition(this->position);
    this->circle.setRotation(this->rotation);
    this->circle.setScale(this->scale);
}

RectangleObject::RectangleObject()
{
    this->visible = true;
    this->Object::Object();
}

RectangleObject::RectangleObject(bool activeState, bool visibility)
{
    this->visible = visibility;
    this->Object::Object(activeState);
}

void RectangleObject::Update()
{
    this->rectangle.setPosition(this->position);
    this->rectangle.setRotation(this->rotation);
    this->rectangle.setScale(this->scale);
}

ConvexObject::ConvexObject()
{
    this->visible = true;
    this->Object::Object();
}

ConvexObject::ConvexObject(bool activeState, bool visibility)
{
    this->visible = visibility;
    this->Object::Object(activeState);
}

void ConvexObject::Update()
{
    this->convexShape.setPosition(this->position);
    this->convexShape.setRotation(this->rotation);
    this->convexShape.setScale(this->scale);
}
