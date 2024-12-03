#include "Object.h"

void Object::SetPosition(sf::Vector2f newPosition)
{
    this->localPosition = newPosition;
}

void Object::SetRotation(float newRotation)
{
    this->localRotation = newRotation;
}

void Object::SetScale(sf::Vector2f newScale)
{
    this->localScale = newScale;
}

Object::Object()
{
    this->active = true;
    this->visible = true;

    this->localPosition = this->sprite.getPosition();
    this->localRotation = this->sprite.getRotation();
    this->localScale = this->sprite.getScale();
}

Object::Object(bool activeState, bool visibility)
{
    this->active = activeState;
    this->visible - visibility;

    this->localPosition = this->sprite.getPosition();
    this->localRotation = this->sprite.getRotation();
    this->localScale = this->sprite.getScale();
}

Object::~Object()
{
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
    this->sprite.setPosition(this->localPosition);
    this->sprite.setRotation(this->localRotation);
    this->sprite.setScale(this->localScale);
}

bool Object::IsVisible()
{
    return this->visible;
}

void Object::SetVisible(bool v)
{
    this->visible = v;
}

sf::Vector2f Object::GetPosition()
{
    return this->localPosition;
}

float Object::GetRotation()
{
    return this->localRotation;
}

sf::Vector2f Object::GetScale()
{
    return this->localScale;
}

sf::Vector2f Object::GetOrigin()
{
    return this->sprite.getOrigin();
}
