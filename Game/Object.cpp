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
}

void Object::Delete()
{
    std::cout << "Object destroyed: " << this << std::endl;
    delete this;
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

SpriteObject::SpriteObject() : Object()
{
    this->visible = true;
}

SpriteObject::SpriteObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

void SpriteObject::Update()
{
    this->sprite.setPosition(this->position);
    this->sprite.setRotation(this->rotation);
    this->sprite.setScale(this->scale);
}

bool SpriteObject::IsVisible()
{
    return this->visible;
}

void SpriteObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

sf::Sprite SpriteObject::GetSprite()
{
    return this->sprite;
}

TextObject::TextObject() : Object()
{
    this->visible = true;
}

TextObject::TextObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

void TextObject::Update()
{
    this->text.setPosition(this->position);
    this->text.setRotation(this->rotation);
    this->text.setScale(this->scale);
}

bool TextObject::IsVisible()
{
    return this->visible;
}

void TextObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

sf::Text TextObject::GetText()
{
    return this->text;
}

CircleObject::CircleObject() : Object()
{
    this->visible = true;
}

CircleObject::CircleObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

void CircleObject::Update()
{
    this->circle.setPosition(this->position);
    this->circle.setRotation(this->rotation);
    this->circle.setScale(this->scale);
}

bool CircleObject::IsVisible()
{
    return this->visible;
}

void CircleObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

sf::CircleShape CircleObject::GetCircleShape()
{
    return this->circle;
}

RectangleObject::RectangleObject() : Object()
{
    this->visible = true;
}

RectangleObject::RectangleObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

void RectangleObject::Update()
{
    this->rectangle.setPosition(this->position);
    this->rectangle.setRotation(this->rotation);
    this->rectangle.setScale(this->scale);
}

bool RectangleObject::IsVisible()
{
    return this->visible;
}

void RectangleObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

sf::RectangleShape RectangleObject::GetRectangleShape()
{
    return this->rectangle;
}

ConvexObject::ConvexObject() : Object()
{
    this->visible = true;
}

ConvexObject::ConvexObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

void ConvexObject::Update()
{
    this->convexShape.setPosition(this->position);
    this->convexShape.setRotation(this->rotation);
    this->convexShape.setScale(this->scale);
}

bool ConvexObject::IsVisible()
{
    return this->visible;
}

void ConvexObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

sf::ConvexShape ConvexObject::GetConvexShape()
{
    return this->convexShape;
}
