#include "Object.h"

void Object::SetPosition(sf::Vector2f newPosition)
{
    this->position = newPosition;
}

void Object::Move(sf::Vector2f direction, float speed)
{
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
        direction /= magnitude;
    this->position += direction * speed;
}

void Object::SetRotation(float newRotation)
{
    this->rotation = newRotation;
}

void Object::Rotate(float angle, float speed)
{
    this->rotation += angle * speed;
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

void SpriteObject::Update()
{
    this->sprite.setPosition(this->GetPosition());
    this->sprite.setRotation(this->GetRotation());
    this->sprite.setScale(this->GetScale());
}

sf::Sprite SpriteObject::GetSprite()
{
    return this->sprite;
}

void TextObject::Update()
{
    this->text.setPosition(this->GetPosition());
    this->text.setRotation(this->GetRotation());
    this->text.setScale(this->GetScale());
}

sf::Text TextObject::GetText()
{
    return this->text;
}

void CircleObject::Update()
{
    this->circle.setPosition(this->GetPosition());
    this->circle.setRotation(this->GetRotation());
    this->circle.setScale(this->GetScale());
}

sf::CircleShape CircleObject::GetCircleShape()
{
    return this->circle;
}

void RectangleObject::Update()
{
    this->rectangle.setPosition(this->GetPosition());
    this->rectangle.setRotation(this->GetRotation());
    this->rectangle.setScale(this->GetScale());
}

sf::RectangleShape RectangleObject::GetRectangleShape()
{
    return this->rectangle;
}

void ConvexObject::Update()
{
    this->convexShape.setPosition(this->GetPosition());
    this->convexShape.setRotation(this->GetRotation());
    this->convexShape.setScale(this->GetScale());
}

sf::ConvexShape ConvexObject::GetConvexShape()
{
    return this->convexShape;
}

void VisibleObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

VisibleObject::VisibleObject() : Object()
{
    this->visible = true;
}

VisibleObject::VisibleObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

bool VisibleObject::IsVisible()
{
    Child *c;
    VisibleObject *p;
    if (c = dynamic_cast<Child *>(this))
        if (p = dynamic_cast<VisibleObject *>(c->GetParent()))
            return p->IsVisible() && this->visible;

    return this->visible;
}
