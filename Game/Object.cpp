#include "Object.h"

bool Collider::showColliders = false;

void Collider::ToggleDebug(bool state)
{
    Collider::showColliders = state;
}

bool Collider::IsDebugEnabled()
{
    return Collider::showColliders;
}

// Object

Object::Object() : name("Object"), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

    LOG("Created: " << this->name << '-' << this << " with no parent");
}

Object::Object(std::string name) : name(name), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

    LOG("Created: " << this->name << '-' << this << " with no parent");
}

Object::Object(int layer) : name("Object"), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

    LOG("Created: " << this->name << '-' << this << " with no parent");
}

Object::Object(Object *parent) : name("Object"), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

        LOG("Created: " << this->name << '-' << this
                        << " with no parent (NULL pointer)");
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        LOG("Created: " << this->name << '-' << this
                        << " with parent: " << parent->name << '-' << parent);
    }
}

Object::Object(std::string name, int layer) : name(name), hasParent(false), parent(nullptr)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

    LOG("Created: " << this->name << '-' << this << " with no parent");
}

Object::Object(std::string name, Object *parent) : name(name), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = 0;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

        LOG("Created: " << this->name << '-' << this
                        << " with no parent (NULL pointer)");
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        LOG("Created: " << this->name << '-' << this
                        << " with parent: " << parent->name << '-' << parent);
    }
}

Object::Object(int layer, Object *parent) : name("Object"), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

        LOG("Created: " << this->name << '-' << this
                        << " with no parent (NULL pointer)");
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        LOG("Created: " << this->name << '-' << this
                        << " with parent: " << parent->name << '-' << parent);
    }
}

Object::Object(std::string name, int layer, Object *parent) : name(name), hasParent(parent != nullptr), parent(parent)
{
    // Initialize default values
    this->layer = layer;
    this->newLayer = 0;
    this->registered = false;
    this->objectIndex = 0;
    this->colliderIndex = 0;
    this->active = true;
    this->parentActive = true;
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

        LOG("Created: " << this->name << '-' << this
                        << " with no parent (NULL pointer)");
    }
    else
    {
        // If the parent exists the object is created as a child of the parent

        // Initialize global transform based on parent
        this->globalPosition = this->parent->globalPosition;
        this->globalRotation = this->parent->globalRotation;
        this->globalScale = this->parent->globalScale;

        LOG("Created: " << this->name << '-' << this
                        << " with parent: " << parent->name << '-' << parent);
    }
}

Object::~Object()
{
    this->registered = false;
    LOG("Deleted: " << this->name << '-' << this);
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
    return this->active && this->parentActive;
}

void Object::SetActive(bool a)
{
    this->active = a;

    // Set objects children and all of their children global active state
    if (a == false || (a == true && this->parentActive == true))
    {
        std::vector<Object *> allChildren = this->GetChildren();
        for (int j = 0; j < allChildren.size(); j++)
        {
            Object *c = allChildren.at(j);
            allChildren[j] = nullptr;

            if (!c || !c->IsRegistered())
                continue;

            c->parentActive = a;

            if (!c->active)
                continue;

            const std::vector<Object *> &children = c->GetChildren();
            allChildren.insert(allChildren.end(), children.begin(), children.end());
            c->children.clear();
        }
    }
}

bool Object::IsVisible()
{
    return this->visible;
}

bool Object::IsCollider()
{
    return false;
}

bool Object::IsSolid()
{
    return false;
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
    // Updates the global transform based of the parent transform
    this->globalPosition = this->NewGlobalPosition(this->position);
    this->globalRotation = this->NewGlobalRotation(this->rotation);
    this->globalScale = this->NewGlobalScale(this->scale);

    // Update the children of the object
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
        {
            LOG_ERR("Failed to update child (NULL pointer)");
            continue;
        }

        if (!c->IsRegistered())
        {
            LOG_ERR("Failed to update: " << c->name << '-' << c
                                         << " (Not registered to the scene)");
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
            LOG_ERR("Failed to draw child (NULL pointer)");
            continue;
        }

        if (!c->IsRegistered())
        {
            LOG_ERR("Failed to draw: " << c->name << '-' << c
                                       << " (Not registered to the scene)");
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

sf::FloatRect Object::GetBounds()
{
    LOG_ERR("Failed to get bounds of: " << this->name << '-' << this
                                        << " (Not a collider)");
    return sf::FloatRect();
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
        LOG_ERR("Failed to get parent of: " << this->name << '-' << this
                                            << " (Has no parent)");
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

sf::Vector2f Object::NewGlobalPosition(sf::Vector2f newLocalPosition)
{
    if (!(this->hasParent && parent->IsRegistered()))
        return newLocalPosition;

    // Get the parent transform
    float parentRotation = this->parent->globalRotation;
    float parentRotationRad = parentRotation * 3.14159265358979323846 / 180;
    sf::Vector2f parentPosition = this->parent->globalPosition;
    sf::Vector2f parentRight(cos(parentRotationRad), sin(parentRotationRad));
    sf::Vector2f parentUp(-parentRight.y, parentRight.x);
    sf::Vector2f parentScale = this->parent->globalScale;

    // The global position is the sum of the parent position and the local position rotated and scaled by the parent transform
    sf::Vector2f finalPosition;
    finalPosition = newLocalPosition.x * parentRight * parentScale.x + newLocalPosition.y * parentUp * parentScale.y;
    finalPosition = finalPosition + parentPosition;

    return finalPosition;
}

float Object::NewGlobalRotation(float newLocalRotation)
{
    if (!(this->hasParent && parent->IsRegistered()))
        return newLocalRotation;

    return this->parent->globalRotation + newLocalRotation;
}

sf::Vector2f Object::NewGlobalScale(sf::Vector2f newLocalScale)
{
    if (!(this->hasParent && parent->IsRegistered()))
        return newLocalScale;

    sf::Vector2f parentScale = this->parent->globalScale;
    return sf::Vector2f(parentScale.x * newLocalScale.x, parentScale.y * newLocalScale.y);
}

void Object::AddChild(Object *c)
{
    // Verify the child to exist
    if (!c)
    {
        LOG_ERR("Failed to add child (NULL pointer)");
        return;
    }

    this->children.push_back(c);
    c->objectIndex = this->children.size() - 1;
    LOG("Added: " << c->name << '-' << c
                  << " to: " << this->name << '-' << this
                  << " children list");
}

void Object::RemoveChild(Object *c)
{
    // Verify the child to exist
    if (!c || !c->IsRegistered())
    {
        LOG_ERR("Failed to remove child (NULL pointer or not registered)");
        return;
    }

    // Verify the child to be in the children list
    size_t index = c->objectIndex;
    if (!(index < this->children.size() && this->children[index] == c))
    {
        LOG_ERR("Failed to remove: " << c->name << '-' << c
                                     << " from: " << this->name << '-' << this
                                     << " children list (Not found in list)");
        return;
    }

    // Remove the child from the list of children
    children.at(index) = this->children.back();
    children.at(index)->objectIndex = index;
    this->children.pop_back();
    LOG("Removed: " << c->name << '-' << c
                    << " from: " << this->name << '-' << this
                    << " children list");
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

void SpriteObject::SetTexture(const sf::Texture &texture, bool resetRect)
{
    this->sprite.setTexture(texture, resetRect);
}

void SpriteObject::SetTextureRect(const sf::IntRect &rectangle)
{
    this->sprite.setTextureRect(rectangle);
}

void SpriteObject::SetColor(const sf::Color &color)
{
    this->sprite.setColor(color);
}

void SpriteObject::SetOrigin(const sf::Vector2f &origin)
{
    this->sprite.setOrigin(origin);
}

const sf::Vector2f &SpriteObject::GetOrigin() const
{
    return this->sprite.getOrigin();
}

const sf::Texture *SpriteObject::GetTexture() const
{
    return this->sprite.getTexture();
}

const sf::IntRect &SpriteObject::GetTextureRect() const
{
    return this->sprite.getTextureRect();
}

const sf::Color &SpriteObject::GetColor() const
{
    return this->sprite.getColor();
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

void TextObject::SetString(const sf::String &string)
{
    this->text.setString(string);
}

void TextObject::SetFont(const sf::Font &font)
{
    this->text.setFont(font);
}

void TextObject::SetCharacterSize(unsigned int size)
{
    this->text.setCharacterSize(size);
}

void TextObject::SetLineSpacing(float spacingFactor)
{
    this->text.setLineSpacing(spacingFactor);
}

void TextObject::SetLetterSpacing(float spacingFactor)
{
    this->text.setLetterSpacing(spacingFactor);
}

void TextObject::SetStyle(sf::Uint32 style)
{
    this->text.setStyle(style);
}

void TextObject::SetFillColor(const sf::Color &color)
{
    this->text.setFillColor(color);
}

void TextObject::SetOutlineColor(const sf::Color &color)
{
    this->text.setOutlineColor(color);
}

void TextObject::SetOutlineThickness(float thickness)
{
    this->text.setOutlineThickness(thickness);
}

sf::Vector2f TextObject::FindCharacterPos(std::size_t index) const
{
    return this->text.findCharacterPos(index);
}

void TextObject::SetOrigin(const sf::Vector2f &origin)
{
    this->text.setOrigin(origin);
}

const sf::Vector2f &TextObject::GetOrigin() const
{
    return this->text.getOrigin();
}

const sf::String &TextObject::GetString() const
{
    return this->text.getString();
}

const sf::Font *TextObject::GetFont() const
{
    return this->text.getFont();
}

unsigned int TextObject::GetCharacterSize() const
{
    return this->text.getCharacterSize();
}

float TextObject::GetLetterSpacing() const
{
    return this->text.getLetterSpacing();
}

float TextObject::GetLineSpacing() const
{
    return this->text.getLineSpacing();
}

sf::Uint32 TextObject::GetStyle() const
{
    return this->text.getStyle();
}

const sf::Color &TextObject::GetFillColor() const
{
    return this->text.getFillColor();
}

const sf::Color &TextObject::getOutlineColor() const
{
    return this->text.getOutlineColor();
}

float TextObject::GetOutlineThickness() const
{
    return this->text.getOutlineThickness();
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

void CircleObject::SetRadius(float radius)
{
    this->circle.setRadius(radius);
}

void CircleObject::SetPointCount(std::size_t count)
{
    this->circle.setPointCount(count);
}

sf::Vector2f CircleObject::GetPoint(std::size_t index) const
{
    return this->circle.getPoint(index);
}

void CircleObject::SetTexture(const sf::Texture *texture, bool resetRect)
{
    this->circle.setTexture(texture, resetRect);
}

void CircleObject::SetTextureRect(const sf::IntRect &rectangle)
{
    this->circle.setTextureRect(rectangle);
}

void CircleObject::SetFillColor(const sf::Color &color)
{
    this->circle.setFillColor(color);
}

void CircleObject::SetOutlineColor(const sf::Color &color)
{
    this->circle.setOutlineColor(color);
}

void CircleObject::setOutlineThickness(float thickness)
{
    this->circle.setOutlineThickness(thickness);
}

void CircleObject::SetOrigin(const sf::Vector2f &origin)
{
    this->circle.setOrigin(origin);
}

const sf::Vector2f &CircleObject::GetOrigin() const
{
    return this->circle.getOrigin();
}

float CircleObject::GetRadius() const
{
    return this->circle.getRadius();
}

std::size_t CircleObject::GetPointCount() const
{
    return this->circle.getPointCount();
}

const sf::Texture *CircleObject::GetTexture() const
{
    return this->circle.getTexture();
}

const sf::IntRect &CircleObject::GetTextureRect() const
{
    return this->circle.getTextureRect();
}

const sf::Color &CircleObject::GetFillColor() const
{
    return this->circle.getFillColor();
}

const sf::Color &CircleObject::GetOutlineColor() const
{
    return this->circle.getOutlineColor();
}

float CircleObject::GetOutlineThickness() const
{
    return this->circle.getOutlineThickness();
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

void RectangleObject::SetSize(const sf::Vector2f &size)
{
    this->rectangle.setSize(size);
}

sf::Vector2f RectangleObject::GetPoint(std::size_t index) const
{
    return this->rectangle.getPoint(index);
}

void RectangleObject::SetTexture(const sf::Texture *texture, bool resetRect)
{
    this->rectangle.setTexture(texture, resetRect);
}

void RectangleObject::SetTextureRect(const sf::IntRect &rectangle)
{
    this->rectangle.setTextureRect(rectangle);
}

void RectangleObject::SetFillColor(const sf::Color &color)
{
    this->rectangle.setFillColor(color);
}

void RectangleObject::SetOutlineColor(const sf::Color &color)
{
    this->rectangle.setOutlineColor(color);
}

void RectangleObject::setOutlineThickness(float thickness)
{
    this->rectangle.setOutlineThickness(thickness);
}

void RectangleObject::SetOrigin(const sf::Vector2f &origin)
{
    this->rectangle.setOrigin(origin);
}

const sf::Vector2f &RectangleObject::GetOrigin() const
{
    return this->rectangle.getOrigin();
}

const sf::Vector2f &RectangleObject::GetSize() const
{
    return this->rectangle.getSize();
}

std::size_t RectangleObject::GetPointCount() const
{
    return this->rectangle.getPointCount();
}

const sf::Texture *RectangleObject::GetTexture() const
{
    return this->rectangle.getTexture();
}

const sf::IntRect &RectangleObject::GetTextureRect() const
{
    return this->rectangle.getTextureRect();
}

const sf::Color &RectangleObject::GetFillColor() const
{
    return this->rectangle.getFillColor();
}

const sf::Color &RectangleObject::GetOutlineColor() const
{
    return this->rectangle.getOutlineColor();
}

float RectangleObject::GetOutlineThickness() const
{
    return this->rectangle.getOutlineThickness();
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

void ConvexObject::SetPointCount(std::size_t count)
{
    this->convexShape.setPointCount(count);
}

void ConvexObject::SetPoint(std::size_t index, const sf::Vector2f &point)
{
    this->convexShape.setPoint(index, point);
}

sf::Vector2f ConvexObject::GetPoint(std::size_t index) const
{
    return this->convexShape.getPoint(index);
}

void ConvexObject::SetTexture(const sf::Texture *texture, bool resetRect)
{
    this->convexShape.setTexture(texture, resetRect);
}

void ConvexObject::SetTextureRect(const sf::IntRect &convexShape)
{
    this->convexShape.setTextureRect(convexShape);
}

void ConvexObject::SetFillColor(const sf::Color &color)
{
    this->convexShape.setFillColor(color);
}

void ConvexObject::SetOutlineColor(const sf::Color &color)
{
    this->convexShape.setOutlineColor(color);
}

void ConvexObject::setOutlineThickness(float thickness)
{
    this->convexShape.setOutlineThickness(thickness);
}

void ConvexObject::SetOrigin(const sf::Vector2f &origin)
{
    this->convexShape.setOrigin(origin);
}

const sf::Vector2f &ConvexObject::GetOrigin() const
{
    return this->convexShape.getOrigin();
}

std::size_t ConvexObject::GetPointCount() const
{
    return this->convexShape.getPointCount();
}

const sf::Texture *ConvexObject::GetTexture() const
{
    return this->convexShape.getTexture();
}

const sf::IntRect &ConvexObject::GetTextureRect() const
{
    return this->convexShape.getTextureRect();
}

const sf::Color &ConvexObject::GetFillColor() const
{
    return this->convexShape.getFillColor();
}

const sf::Color &ConvexObject::GetOutlineColor() const
{
    return this->convexShape.getOutlineColor();
}

float ConvexObject::GetOutlineThickness() const
{
    return this->convexShape.getOutlineThickness();
}

// Collider

Collider::Collider() : RectangleObject()
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(std::string name) : RectangleObject(name)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(int layer) : RectangleObject(layer)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(Object *parent) : RectangleObject(parent)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(std::string name, int layer) : RectangleObject(name, layer)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(std::string name, Object *parent) : RectangleObject(name, parent)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(int layer, Object *parent) : RectangleObject(layer, parent)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}
Collider::Collider(std::string name, int layer, Object *parent) : RectangleObject(name, layer, parent)
{
    this->solidState = false;
    this->SetFillColor(sf::Color::Transparent);
    this->SetOutlineColor(sf::Color::Red);
    this->setOutlineThickness(1);
}

bool Collider::IsVisible()
{
    return Collider::showColliders && this->Object::IsVisible();
}

bool Collider::IsCollider()
{
    return true;
}

bool Collider::IsSolid()
{
    return this->solidState;
}

void Collider::SetSolid(bool solid)
{
    this->solidState = solid;
}

sf::FloatRect Collider::GetBounds()
{
    offsetRectangle.setSize(this->rectangle.getSize());
    offsetRectangle.setOrigin(this->rectangle.getOrigin());
    offsetRectangle.setOutlineThickness(this->rectangle.getOutlineThickness());
    offsetRectangle.setPosition(this->NewGlobalPosition(this->GetPosition()));
    offsetRectangle.setRotation(this->NewGlobalRotation(this->GetRotation()));
    offsetRectangle.setScale(this->NewGlobalScale(this->GetScale()));
    return offsetRectangle.getGlobalBounds();
}

sf::FloatRect Collider::GetBoundsOffsetPosition(sf::Vector2f offset)
{
    offsetRectangle.setSize(this->rectangle.getSize());
    offsetRectangle.setOrigin(this->rectangle.getOrigin());
    offsetRectangle.setOutlineThickness(this->rectangle.getOutlineThickness());
    offsetRectangle.setPosition(this->NewGlobalPosition(this->GetPosition() + offset));
    offsetRectangle.setRotation(this->NewGlobalRotation(this->GetRotation()));
    offsetRectangle.setScale(this->NewGlobalScale(this->GetScale()));
    return offsetRectangle.getGlobalBounds();
}

sf::FloatRect Collider::GetBoundsOffsetRotation(float offset)
{
    offsetRectangle.setSize(this->rectangle.getSize());
    offsetRectangle.setOrigin(this->rectangle.getOrigin());
    offsetRectangle.setOutlineThickness(this->rectangle.getOutlineThickness());
    offsetRectangle.setPosition(this->NewGlobalPosition(this->GetPosition()));
    offsetRectangle.setRotation(this->NewGlobalRotation(this->GetRotation() + offset));
    offsetRectangle.setScale(this->NewGlobalScale(this->GetScale()));
    return offsetRectangle.getGlobalBounds();
}

sf::FloatRect Collider::GetBoundsOffsetScale(sf::Vector2f offset)
{
    offsetRectangle.setSize(this->rectangle.getSize());
    offsetRectangle.setOrigin(this->rectangle.getOrigin());
    offsetRectangle.setOutlineThickness(this->rectangle.getOutlineThickness());
    offsetRectangle.setPosition(this->NewGlobalPosition(this->GetPosition()));
    offsetRectangle.setRotation(this->NewGlobalRotation(this->GetRotation()));
    offsetRectangle.setScale(this->NewGlobalScale({this->GetScale().x * offset.x, this->GetScale().y * offset.y}));
    return offsetRectangle.getGlobalBounds();
}
