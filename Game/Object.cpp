#include "Object.h"

// Object

Object::Object() : name("Object"), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    std::cout << "Created: " << this->name << '-' << this
              << " with no parent" << std::endl;
}

Object::Object(std::string name) : name(name), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    std::cout << "Created: " << this->name << '-' << this
              << " with no parent" << std::endl;
}

Object::Object(int layer) : name("Object"), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

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

Object::Object(Object *parent) : name("Object"), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this
                  << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        std::cout << "Created: " << this->name << '-' << this
                  << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::Object(std::string name, int layer) : name(name), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Initialize global transform
    this->globalPosition = sf::Vector2f(0, 0);
    this->globalRotation = 0;
    this->globalScale = sf::Vector2f(1, 1);

    std::cout << "Created: " << this->name << '-' << this
              << " with no parent" << std::endl;
}

Object::Object(std::string name, Object *parent) : name(name), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this
                  << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        std::cout << "Created: " << this->name << '-' << this
                  << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::Object(int layer, Object *parent) : name("Object"), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this
                  << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        std::cout << "Created: " << this->name << '-' << this
                  << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::Object(std::string name, int layer, Object *parent) : name(name), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->active = true;
    this->visible = true;
    this->newParent = nullptr;
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;

    // Initialize local transform
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    // Verify the parent to exist
    if (!parent)
    {
        // If the parent doesn't exist the object is created without a parent

        // Initialize global transform
        this->globalPosition = sf::Vector2f(0, 0);
        this->globalRotation = 0;
        this->globalScale = sf::Vector2f(1, 1);

        std::cout << "Created: " << this->name << '-' << this
                  << " with no parent (NULL pointer)" << std::endl;
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        std::cout << "Created: " << this->name << '-' << this
                  << " with parent: " << parent->name << '-' << parent << std::endl;
    }
}

Object::~Object()
{
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->subscriberIndices.clear();
    this->active = false;
    this->visible = false;
    this->parent = nullptr;
    this->newParent = nullptr;
    this->hasParent = false;
    this->globalPosition = {0, 0};
    this->globalRotation = 0;
    this->globalScale = {0, 0};
    this->position = {0, 0};
    this->rotation = 0;
    this->scale = {0, 0};
    this->toBeDeleted = false;
    this->toChangeParent = false;
    this->toBeMoved = false;
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

bool Object::IsRegistered()
{
    return this->registered;
}

void Object::SetPosition(sf::Vector2f newPosition)
{
    this->position = newPosition;
}

void Object::Move(sf::Vector2f direction, float speed, float dt)
{
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
        direction /= magnitude;
    this->position += direction * speed * dt;
}

void Object::SetRotation(float newRotation)
{
    this->rotation = newRotation;
}

void Object::Rotate(float angle, float speed, float dt)
{
    this->rotation += angle * speed * dt;
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
    if (this->hasParent && parent->IsRegistered())
    {
        // Updates the global transform based of the parent transform

        // Get the parent transform
        float parentRotation = this->parent->globalRotation;
        float parentRotationRad = parentRotation * 3.14159265358979323846 / 180;
        sf::Vector2f parentPosition = this->parent->globalPosition;
        sf::Vector2f parentRight(cos(parentRotationRad), sin(parentRotationRad));
        sf::Vector2f parentUp(-parentRight.y, parentRight.x);
        sf::Vector2f parentScale = this->parent->globalScale;

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

        if (!c->IsRegistered())
        {
            std::cout << "Failed to update: " << c->name << '-' << c
                      << " (Not registered to the scene)" << std::endl;
            continue;
        }

        if (c->active)
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

        if (!c->IsRegistered())
        {
            std::cout << "Failed to draw: " << c->name << '-' << c
                      << " (Not registered to the scene)" << std::endl;
            continue;
        }

        if (c->visible)
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
        std::cout << "Failed to get parent of: " << this->name << '-' << this
                  << " (Has no parent)" << std::endl;
        return nullptr;
    }

    return this->parent;
}

const std::vector<Object *> &Object::GetChildren()
{
    return this->children;
}

const std::vector<Object *> Object::GetChildrenToAdd()
{
    return std::vector<Object *>();
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
    c->objectIndex = this->children.size() - 1;
    std::cout << "Added: " << c->name << '-' << c
              << " to: " << this->name << '-' << this
              << " children list" << std::endl;
}

void Object::RemoveChild(Object *c)
{
    // Verify the child to exist
    if (!c || !c->IsRegistered())
    {
        std::cout << "Failed to remove child (NULL pointer or not registered)" << std::endl;
        return;
    }

    // Verify the child to be in the children list
    size_t index = c->objectIndex;
    if (!(index < this->children.size() && this->children[index] == c))
    {
        std::cout << "Failed to remove: " << c->name << '-' << c
                  << " from: " << this->name << '-' << this
                  << " children list (Not found in list)" << std::endl;
        return;
    }

    // Remove the child from the list of children
    children.at(index) = this->children.back();
    children.at(index)->objectIndex = index;
    this->children.pop_back();
    std::cout << "Removed: " << c->name << '-' << c
              << " from: " << this->name << '-' << this
              << " children list" << std::endl;
}

const std::vector<sf::Event::EventType> Object::GetEventsToSubscribe()
{
    return std::vector<sf::Event::EventType>();
}

bool Object::IsMarkedToBeDeleted()
{
    return this->toBeDeleted;
}

bool Object::IsMarkedToChangeParent()
{
    return this->toChangeParent;
}

bool Object::IsMarkedToBeMoved()
{
    return this->toBeMoved;
}

// SpriteObject

SpriteObject::SpriteObject() : Object()
{
}
SpriteObject::SpriteObject(std::string name) : Object(name)
{
}
SpriteObject::SpriteObject(int layer) : Object(layer)
{
}
SpriteObject::SpriteObject(Object *parent) : Object(parent)
{
}
SpriteObject::SpriteObject(std::string name, int layer) : Object(name, layer)
{
}
SpriteObject::SpriteObject(std::string name, Object *parent) : Object(name, parent)
{
}
SpriteObject::SpriteObject(int layer, Object *parent) : Object(layer, parent)
{
}
SpriteObject::SpriteObject(std::string name, int layer, Object *parent) : Object(name, layer, parent)
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

TextObject::TextObject() : Object()
{
}
TextObject::TextObject(std::string name) : Object(name)
{
}
TextObject::TextObject(int layer) : Object(layer)
{
}
TextObject::TextObject(Object *parent) : Object(parent)
{
}
TextObject::TextObject(std::string name, int layer) : Object(name, layer)
{
}
TextObject::TextObject(std::string name, Object *parent) : Object(name, parent)
{
}
TextObject::TextObject(int layer, Object *parent) : Object(layer, parent)
{
}
TextObject::TextObject(std::string name, int layer, Object *parent) : Object(name, layer, parent)
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

CircleObject::CircleObject() : Object()
{
}
CircleObject::CircleObject(std::string name) : Object(name)
{
}
CircleObject::CircleObject(int layer) : Object(layer)
{
}
CircleObject::CircleObject(Object *parent) : Object(parent)
{
}
CircleObject::CircleObject(std::string name, int layer) : Object(name, layer)
{
}
CircleObject::CircleObject(std::string name, Object *parent) : Object(name, parent)
{
}
CircleObject::CircleObject(int layer, Object *parent) : Object(layer, parent)
{
}
CircleObject::CircleObject(std::string name, int layer, Object *parent) : Object(name, layer, parent)
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

RectangleObject::RectangleObject() : Object()
{
}
RectangleObject::RectangleObject(std::string name) : Object(name)
{
}
RectangleObject::RectangleObject(int layer) : Object(layer)
{
}
RectangleObject::RectangleObject(Object *parent) : Object(parent)
{
}
RectangleObject::RectangleObject(std::string name, int layer) : Object(name, layer)
{
}
RectangleObject::RectangleObject(std::string name, Object *parent) : Object(name, parent)
{
}
RectangleObject::RectangleObject(int layer, Object *parent) : Object(layer, parent)
{
}
RectangleObject::RectangleObject(std::string name, int layer, Object *parent) : Object(name, layer, parent)
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

ConvexObject::ConvexObject() : Object()
{
}
ConvexObject::ConvexObject(std::string name) : Object(name)
{
}
ConvexObject::ConvexObject(int layer) : Object(layer)
{
}
ConvexObject::ConvexObject(Object *parent) : Object(parent)
{
}
ConvexObject::ConvexObject(std::string name, int layer) : Object(name, layer)
{
}
ConvexObject::ConvexObject(std::string name, Object *parent) : Object(name, parent)
{
}
ConvexObject::ConvexObject(int layer, Object *parent) : Object(layer, parent)
{
}
ConvexObject::ConvexObject(std::string name, int layer, Object *parent) : Object(name, layer, parent)
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
