#include "Object.h"

// Object

Object::Object(Scene *scene)
{
    // Initialize default values
    this->scene = scene;
    this->layer = 0;
    this->name = "Object";
    this->active = true;
    this->visible = true;
    this->hasParent = false;
    this->toBeDeleted = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    std::cout << "Created: " << this->name << '-' << this << " with no parent" << std::endl;
}

Object::Object(Scene *scene, std::string name)
{
    // Initialize default values
    this->scene = scene;
    this->layer = 0;
    this->name = name;
    this->active = true;
    this->visible = true;
    this->hasParent = false;
    this->toBeDeleted = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    std::cout << "Created: " << this->name << '-' << this << " with no parent" << std::endl;
}

Object::Object(Scene *scene, Object *parent)
{
    // Initialize default values
    this->scene = scene;
    this->layer = 0;
    this->name = "Object";
    this->active = true;
    this->visible = true;
    this->toBeDeleted = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent
        this->parent = nullptr;
        hasParent = false;

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent
        this->parent = parent;
        hasParent = true;

        // Initialize global transform based on parent
        this->globalPosition = this->parent->GetGlobalPosition();
        this->globalRotation = this->parent->GetGlobalRotation();
        this->globalScale = this->parent->GetGlobalScale();

        std::cout << "Created: " << this->name << '-' << this << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::Object(Scene *scene, std::string name, Object *parent)
{
    // Initialize default values
    this->scene = scene;
    this->layer = 0;
    this->name = name;
    this->active = true;
    this->visible = true;
    this->toBeDeleted = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent
        this->parent = nullptr;
        hasParent = false;

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent
        this->parent = parent;
        hasParent = true;

        // Initialize global transform based on parent
        this->globalPosition = this->parent->GetGlobalPosition();
        this->globalRotation = this->parent->GetGlobalRotation();
        this->globalScale = this->parent->GetGlobalScale();

        std::cout << "Created: " << this->name << '-' << this << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::~Object()
{
    std::cout << "Deleted: " << this->name << '-' << this << std::endl;
}

std::string Object::GetName()
{
    return this->name;
}

int Object::GetLayer()
{
    return this->layer;
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

void Object::SetLayer(int l)
{
    this->layer = l;
}

void Object::SetActive(bool a)
{
    this->active = a;
}

bool Object::IsVisible()
{
    return this->visible;
}

void Object::SetVisible(bool visibility)
{
    this->visible = visibility;
}

void Object::OnEvent(sf::Event event)
{
}

void Object::Update()
{
    if (this->hasParent)
    {
        // Updates the global transform based of the parent transform

        // Get the parent transform
        float parentRotation = this->parent->GetGlobalRotation();
        float parentRotationRad = parentRotation * M_PI / 180;
        sf::Vector2f parentPosition = this->parent->GetGlobalPosition();
        sf::Vector2f parentRight(cos(parentRotationRad), sin(parentRotationRad));
        sf::Vector2f parentUp(-parentRight.y, parentRight.x);
        sf::Vector2f parentScale = this->parent->GetGlobalScale();

        // The global position is the sum of the parent position and the local position rotated and scaled by the parent transform
        sf::Vector2f finalPosition;
        finalPosition = this->position.x * parentRight * parentScale.x + this->position.y * parentUp * parentScale.y;
        finalPosition = finalPosition + parentPosition;
        this->globalPosition = finalPosition;

        // The global rotation is the sum of the parent rotation and the local rotation
        this->globalRotation = parentRotation + this->rotation;

        // The global scale is the product of the parent scale and the local scale
        this->globalScale = sf::Vector2f(parentScale.x * this->scale.x, parentScale.y * this->scale.y);
    }
    else
    {
        // If the object has no parent the global transform is the same as the local transform
        this->globalPosition = this->position;
        this->globalRotation = this->rotation;
        this->globalScale = this->scale;
    }

    // Update the children of the object
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
        {
            std::cout << "Failed to update child (NULL pointer)" << std::endl;
            continue;
        }

        if (c->IsActive())
            c->Update();
    }
}

void Object::Draw(sf::RenderWindow &window)
{
    // Draw the children of the object
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
        {
            std::cout << "Failed to draw child (NULL pointer)" << std::endl;
            continue;
        }

        if (c->IsVisible())
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
        std::cout << "Failed to get parent of: " << this->name << '-' << this << " (Has no parent)" << std::endl;
        return nullptr;
    }

    return this->parent;
}

const std::vector<Object *> &Object::GetChildren()
{
    return this->children;
}

void Object::AddChild(Object *c)
{
    // Verify the child to exist
    if (!c)
    {
        std::cout << "Failed to add child (NULL pointer)" << std::endl;
        return;
    }

    this->children.push_back(c);
    std::cout << "Added: " << c->name << '-' << c << " to: " << this->name << '-' << this << " children list" << std::endl;
}

void Object::RemoveChild(Object *c)
{
    // Verify the child to exist
    if (!c)
    {
        std::cout << "Failed to remove child (NULL pointer)" << std::endl;
        return;
    }

    // Find the child in the list of children and verify it to exist
    auto it = std::find(this->children.begin(), this->children.end(), c);
    if (it == this->children.end())
    {
        std::cout << "Failed to remove: " << c->name << '-' << c << " from: " << this->name << '-' << this << " children list (Not found in list)" << std::endl;
        return;
    }

    // Remove the child from the list of children
    *it = this->children.back();
    this->children.pop_back();
    std::cout << "Removed: " << c->name << '-' << c << " from: " << this->name << '-' << this << " children list" << std::endl;
}

const std::vector<sf::Event::EventType> Object::GetEventsToSubscribe()
{
    return std::vector<sf::Event::EventType>();
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

SpriteObject::SpriteObject(Scene *scene) : Object(scene)
{
}
SpriteObject::SpriteObject(Scene *scene, std::string name) : Object(scene, name)
{
}
SpriteObject::SpriteObject(Scene *scene, Object *parent) : Object(scene, parent)
{
}
SpriteObject::SpriteObject(Scene *scene, std::string name, Object *parent) : Object(scene, name, parent)
{
}

void SpriteObject::Update()
{
    // Update the object and its children
    this->Object::Update();

    // Sets the transform to the sprite
    this->sprite.setPosition(this->GetGlobalPosition());
    this->sprite.setRotation(this->GetGlobalRotation());
    this->sprite.setScale(this->GetGlobalScale());
}

void SpriteObject::Draw(sf::RenderWindow &window)
{
    // Draw the sprite
    window.draw(this->sprite);

    // Draw the children of the object
    this->Object::Draw(window);
}

// TextObject

TextObject::TextObject(Scene *scene) : Object(scene)
{
}
TextObject::TextObject(Scene *scene, std::string name) : Object(scene, name)
{
}
TextObject::TextObject(Scene *scene, Object *parent) : Object(scene, parent)
{
}
TextObject::TextObject(Scene *scene, std::string name, Object *parent) : Object(scene, name, parent)
{
}

void TextObject::Update()
{
    // Update the object and its children
    this->Object::Update();

    // Sets the transform to the text
    this->text.setPosition(this->GetGlobalPosition());
    this->text.setRotation(this->GetGlobalRotation());
    this->text.setScale(this->GetGlobalScale());
}

void TextObject::Draw(sf::RenderWindow &window)
{
    // Draw the text
    window.draw(this->text);

    // Draw the children of the object
    this->Object::Draw(window);
}

// CircleObject

CircleObject::CircleObject(Scene *scene) : Object(scene)
{
}
CircleObject::CircleObject(Scene *scene, std::string name) : Object(scene, name)
{
}
CircleObject::CircleObject(Scene *scene, Object *parent) : Object(scene, parent)
{
}
CircleObject::CircleObject(Scene *scene, std::string name, Object *parent) : Object(scene, name, parent)
{
}

void CircleObject::Update()
{
    // Update the object and its children
    this->Object::Update();

    // Sets the transform to the circle
    this->circle.setPosition(this->GetGlobalPosition());
    this->circle.setRotation(this->GetGlobalRotation());
    this->circle.setScale(this->GetGlobalScale());
}

void CircleObject::Draw(sf::RenderWindow &window)
{
    // Draw the circle
    window.draw(this->circle);

    // Draw the children of the object
    this->Object::Draw(window);
}

// RectangleObject

RectangleObject::RectangleObject(Scene *scene) : Object(scene)
{
}
RectangleObject::RectangleObject(Scene *scene, std::string name) : Object(scene, name)
{
}
RectangleObject::RectangleObject(Scene *scene, Object *parent) : Object(scene, parent)
{
}
RectangleObject::RectangleObject(Scene *scene, std::string name, Object *parent) : Object(scene, name, parent)
{
}

void RectangleObject::Update()
{
    // Update the object and its children
    this->Object::Update();

    // Sets the transform to the rectangle
    this->rectangle.setPosition(this->GetGlobalPosition());
    this->rectangle.setRotation(this->GetGlobalRotation());
    this->rectangle.setScale(this->GetGlobalScale());
}

void RectangleObject::Draw(sf::RenderWindow &window)
{
    // Draw the rectangle
    window.draw(this->rectangle);

    // Draw the children of the object
    this->Object::Draw(window);
}

// ConvexObject

ConvexObject::ConvexObject(Scene *scene) : Object(scene)
{
}
ConvexObject::ConvexObject(Scene *scene, Object *parent) : Object(scene, parent)
{
}
ConvexObject::ConvexObject(Scene *scene, std::string name) : Object(scene, name)
{
}
ConvexObject::ConvexObject(Scene *scene, std::string name, Object *parent) : Object(scene, name, parent)
{
}

void ConvexObject::Update()
{
    // Update the object and its children
    this->Object::Update();

    // Sets the transform to the shape
    this->convexShape.setPosition(this->GetGlobalPosition());
    this->convexShape.setRotation(this->GetGlobalRotation());
    this->convexShape.setScale(this->GetGlobalScale());
}

void ConvexObject::Draw(sf::RenderWindow &window)
{
    // Draw the shape
    window.draw(this->convexShape);

    // Draw the children of the object
    this->Object::Draw(window);
}
