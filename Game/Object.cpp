#include "Object.h"

// Object

Object::Object()
{
    this->toBeDeleted = false;
    this->hasParent = false;
    this->active = true;
    this->visible = true;

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    // Initialize transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << " with no parent" << std::endl;
}

Object::Object(Object *p)
{
    // Verify the parent to exist
    if (!p)
    {
        this->parent = nullptr;
        hasParent = false;

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);
    }
    else
    {
        this->parent = p;
        hasParent = true;

        // Initialize global transform based on parent
        this->globalPosition = this->parent->GetGlobalPosition();
        this->globalRotation = this->parent->GetGlobalRotation();
        this->globalScale = this->parent->GetGlobalScale();
    }

    this->toBeDeleted = false;
    this->active = true;
    this->visible = true;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << " with parent: " << p << std::endl;
}

Object::Object(bool activeState)
{
    this->toBeDeleted = false;
    this->hasParent = false;
    this->active = activeState;
    this->visible = true;

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << "with no parent" << std::endl;
}

Object::Object(bool activeState, Object *p)
{
    // Verify the parent to exist
    if (!p)
    {
        this->parent = nullptr;
        hasParent = false;

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);
    }
    else
    {
        this->parent = p;
        hasParent = true;

        // Initialize global transform based on parent
        this->globalPosition = this->parent->GetGlobalPosition();
        this->globalRotation = this->parent->GetGlobalRotation();
        this->globalScale = this->parent->GetGlobalScale();
    }

    this->toBeDeleted = false;
    this->active = activeState;
    this->visible = true;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << " with parent: " << p << std::endl;
}

Object::Object(bool activeState, bool visibility)
{
    this->toBeDeleted = false;
    this->hasParent = false;
    this->active = activeState;
    this->visible = visibility;

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << "with no parent" << std::endl;
}

Object::Object(bool activeState, bool visibility, Object *p)
{
    // Verify the parent to exist
    if (!p)
    {
        this->parent = nullptr;
        hasParent = false;

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);
    }
    else
    {
        this->parent = p;
        hasParent = true;

        // Initialize global transform based on parent
        this->globalPosition = this->parent->GetGlobalPosition();
        this->globalRotation = this->parent->GetGlobalRotation();
        this->globalScale = this->parent->GetGlobalScale();
    }

    this->toBeDeleted = false;
    this->active = activeState;
    this->visible = visibility;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    std::cout << "Object created: " << this << " with parent: " << p << std::endl;
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

void Object::SetVisible(bool visibility)
{
    this->visible = visibility;
}

bool Object::IsVisible()
{
    return this->visible;
}

void Object::OnEvent(sf::Event event)
{
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
            std::cout << "Failed to call child method (Null pointer)" << std::endl;

        else if (c->IsActive())
            c->OnEvent(event);
    }
}

void Object::Update()
{
    if (this->hasParent)
    {
        // Updates the global transform based of the parent transform
        this->globalPosition = this->parent->GetGlobalPosition() + this->position;
        this->globalRotation = this->parent->GetGlobalRotation() + this->rotation;
        this->globalScale = sf::Vector2f(this->parent->GetGlobalScale().x * this->scale.x, this->parent->GetGlobalScale().y * this->scale.y);
    }
    else
    {
        // If the object has no parent the global transform is the same as the local transform
        this->globalPosition = this->position;
        this->globalRotation = this->rotation;
        this->globalScale = this->scale;
    }

    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
            std::cout << "Failed to update child (Null pointer)" << std::endl;

        else if (c->IsActive())
            c->Update();
    }
}

void Object::Draw(sf::RenderWindow *window)
{
    // Verify the window to exist
    if (!window)
    {
        std::cout << "Failed to draw object " << this << " (Null pointer to window)";
        return;
    }

    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
            std::cout << "Failed to draw child (Null pointer)" << std::endl;

        else if (c->IsVisible())
            c->Draw(window);
    }
}

sf::Vector2f Object::GetGlobalPosition()
{
    return this->globalPosition;
}

float Object::GetGlobalRotation()
{
    return this->globalRotation;
}

sf::Vector2f Object::GetGlobalScale()
{
    return this->globalScale;
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

bool Object::IsChild()
{
    return this->hasParent;
}

Object *Object::GetParent()
{
    // Verify the object to have a parent
    if (!this->hasParent)
    {
        std::cout << "Failed to get parent of object " << this << " (Object has no parent)" << std::endl;
        return nullptr;
    }

    return this->parent;
}

const std::list<Object *> &Object::GetChildren()
{
    return this->children;
}

void Object::AddChild(Object *c)
{
    // Verify the child to exist
    if (!c)
    {
        std::cout << "Failed to add child (Null pointer)" << std::endl;
        return;
    }

    this->children.push_back(c);
    std::cout << "Adding child " << c << " to " << this << " children list" << std::endl;
}

void Object::RemoveChild(Object *c)
{
    // Verify the child to exist
    if (!c)
    {
        std::cout << "Failed to remove child (Null pointer)" << std::endl;
        return;
    }

    this->children.remove(c);
    std::cout << "Removed child " << c << " from " << this << " children list" << std::endl;
}

void Object::MarkToBeDeleted()
{
    this->toBeDeleted = true;
}

bool Object::IsMarkedToBeDeleted()
{
    return this->toBeDeleted;
}

// SpriteObject

SpriteObject::SpriteObject() : Object()
{
}
SpriteObject::SpriteObject(Object *p) : Object(p)
{
}
SpriteObject::SpriteObject(bool activeState) : Object(activeState)
{
}
SpriteObject::SpriteObject(bool activeState, Object *p) : Object(activeState, p)
{
}
SpriteObject::SpriteObject(bool activeState, bool visibility) : Object(activeState, visibility)
{
}
SpriteObject::SpriteObject(bool activeState, bool visibility, Object *p) : Object(activeState, visibility, p)
{
}
void SpriteObject::Update()
{
    this->Object::Update();

    // Sets the transform to the sprite
    this->sprite.setPosition(this->GetGlobalPosition());
    this->sprite.setRotation(this->GetGlobalRotation());
    this->sprite.setScale(this->GetGlobalScale());
}

void SpriteObject::Draw(sf::RenderWindow *window)
{
    this->Object::Draw(window);

    window->draw(this->sprite);
}

// TextObject

TextObject::TextObject() : Object()
{
}
TextObject::TextObject(Object *p) : Object(p)
{
}
TextObject::TextObject(bool activeState) : Object(activeState)
{
}
TextObject::TextObject(bool activeState, Object *p) : Object(activeState, p)
{
}
TextObject::TextObject(bool activeState, bool visibility) : Object(activeState, visibility)
{
}
TextObject::TextObject(bool activeState, bool visibility, Object *p) : Object(activeState, visibility, p)
{
}

void TextObject::Update()
{
    this->Object::Update();

    // Sets the transform to the text
    this->text.setPosition(this->GetGlobalPosition());
    this->text.setRotation(this->GetGlobalRotation());
    this->text.setScale(this->GetGlobalScale());
}

void TextObject::Draw(sf::RenderWindow *window)
{
    this->Object::Draw(window);

    window->draw(this->text);
}

// CircleObject

CircleObject::CircleObject() : Object()
{
}
CircleObject::CircleObject(Object *p) : Object(p)
{
}
CircleObject::CircleObject(bool activeState) : Object(activeState)
{
}
CircleObject::CircleObject(bool activeState, Object *p) : Object(activeState, p)
{
}
CircleObject::CircleObject(bool activeState, bool visibility) : Object(activeState, visibility)
{
}
CircleObject::CircleObject(bool activeState, bool visibility, Object *p) : Object(activeState, visibility, p)
{
}

void CircleObject::Update()
{
    this->Object::Update();

    // Sets the transform to the circle
    this->circle.setPosition(this->GetGlobalPosition());
    this->circle.setRotation(this->GetGlobalRotation());
    this->circle.setScale(this->GetGlobalScale());
}

void CircleObject::Draw(sf::RenderWindow *window)
{
    this->Object::Draw(window);

    window->draw(this->circle);
}

// RectangleObject

RectangleObject::RectangleObject() : Object()
{
}
RectangleObject::RectangleObject(Object *p) : Object(p)
{
}
RectangleObject::RectangleObject(bool activeState) : Object(activeState)
{
}
RectangleObject::RectangleObject(bool activeState, Object *p) : Object(activeState, p)
{
}
RectangleObject::RectangleObject(bool activeState, bool visibility) : Object(activeState, visibility)
{
}
RectangleObject::RectangleObject(bool activeState, bool visibility, Object *p) : Object(activeState, visibility, p)
{
}

void RectangleObject::Update()
{
    this->Object::Update();

    // Sets the transform to the rectangle
    this->rectangle.setPosition(this->GetGlobalPosition());
    this->rectangle.setRotation(this->GetGlobalRotation());
    this->rectangle.setScale(this->GetGlobalScale());
}

void RectangleObject::Draw(sf::RenderWindow *window)
{
    this->Object::Draw(window);

    window->draw(this->rectangle);
}

// ConvexObject

ConvexObject::ConvexObject() : Object()
{
}
ConvexObject::ConvexObject(Object *p) : Object(p)
{
}
ConvexObject::ConvexObject(bool activeState) : Object(activeState)
{
}
ConvexObject::ConvexObject(bool activeState, Object *p) : Object(activeState, p)
{
}
ConvexObject::ConvexObject(bool activeState, bool visibility) : Object(activeState, visibility)
{
}
ConvexObject::ConvexObject(bool activeState, bool visibility, Object *p) : Object(activeState, visibility, p)
{
}

void ConvexObject::Update()
{
    this->Object::Update();

    // Sets the transform to the shape
    this->convexShape.setPosition(this->GetGlobalPosition());
    this->convexShape.setRotation(this->GetGlobalRotation());
    this->convexShape.setScale(this->GetGlobalScale());
}

void ConvexObject::Draw(sf::RenderWindow *window)
{
    this->Object::Draw(window);

    window->draw(this->convexShape);
}
