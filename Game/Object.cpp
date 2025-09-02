#include "Object.h"

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

bool Object::IsActive()
{
    return this->active;
}

void Object::SetActive(bool a)
{
    this->active = a;
}

bool Object::IsVisible()
{
    return true;
}

void Object::OnEvent(sf::Event event)
{
}

void Object::Update()
{
}

void Object::Draw(sf::RenderWindow *window)
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

DrawableObject::DrawableObject() : Object()
{
    this->visible = true;
}

DrawableObject::DrawableObject(bool activeState, bool visibility) : Object(activeState)
{
    this->visible = visibility;
}

DrawableObject::~DrawableObject()
{
    std::cout << "Drawable object destroyed " << this << std::endl;
}

bool DrawableObject::IsVisible()
{
    return this->visible;
}

void DrawableObject::SetVisible(bool visibility)
{
    this->visible = visibility;
}

void DrawableObject::Draw(sf::RenderWindow *window)
{
    // Verify the window to exist
    if (!window)
    {
        std::cout << "Failed to draw object " << this << " (Null pointer to window)";
        return;
    }
}

void SpriteObject::Update()
{
    // Sets the transform to the sprite
    this->sprite.setPosition(this->GetPosition());
    this->sprite.setRotation(this->GetRotation());
    this->sprite.setScale(this->GetScale());
}

void SpriteObject::Draw(sf::RenderWindow *window)
{
    this->DrawableObject::Draw(window);

    window->draw(this->sprite);
}

void TextObject::Update()
{
    // Sets the transform to the text
    this->text.setPosition(this->GetPosition());
    this->text.setRotation(this->GetRotation());
    this->text.setScale(this->GetScale());
}

void TextObject::Draw(sf::RenderWindow *window)
{
    this->DrawableObject::Draw(window);

    window->draw(this->text);
}

void CircleObject::Update()
{
    // Sets the transform to the circle
    this->circle.setPosition(this->GetPosition());
    this->circle.setRotation(this->GetRotation());
    this->circle.setScale(this->GetScale());
}

void CircleObject::Draw(sf::RenderWindow *window)
{
    this->DrawableObject::Draw(window);

    window->draw(this->circle);
}

void RectangleObject::Update()
{
    // Sets the transform to the rectangle
    this->rectangle.setPosition(this->GetPosition());
    this->rectangle.setRotation(this->GetRotation());
    this->rectangle.setScale(this->GetScale());
}

void RectangleObject::Draw(sf::RenderWindow *window)
{
    this->DrawableObject::Draw(window);

    window->draw(this->rectangle);
}

void ConvexObject::Update()
{
    // Sets the transform to the shape
    this->convexShape.setPosition(this->GetPosition());
    this->convexShape.setRotation(this->GetRotation());
    this->convexShape.setScale(this->GetScale());
}

void ConvexObject::Draw(sf::RenderWindow *window)
{
    this->DrawableObject::Draw(window);

    window->draw(this->convexShape);
}
