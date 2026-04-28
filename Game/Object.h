#pragma once
#include "Logger.h"
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Base Object class that all objects in the game will inherit from
// The object is a base instance of the game it has a position, rotation, scale
// Has an active state (if it's false the update function will not be called)
// Has a visible state (if it's false the draw function will not be called)
// Can be a parent of other objects that depend on it when it's deleted all its children are deleted
// Can be a child of another object its transform, visibility and active State are dependent of its parent's
class Object
{
private:
    // Name of the object (used for debugging)
    const std::string name;
    // Layer of the object (objects with higher layers are drawn on top of objects with lower layers)
    int layer;
    // layer that the object will move to
    int newLayer;

    // True when the object is completely added to the scene
    bool registered;
    // The index of the object in the layer or in its parent's children list
    size_t objectIndex;
    // The index of the object in the event's subscribers list of the events that is subscribed to
    std::unordered_map<sf::Event::EventType, size_t> subscriberIndices;
    // The index of the object in the colliders list (if it is a collider)
    size_t colliderIndex;

    // Active state of the object (if it's false the update function will not be called)
    bool active;
    // Visible state of the object (if it's false the draw function will not be called)
    bool visible;

    // Parent of the object (if it has one)
    Object *parent;
    // Parent that the object will move to
    Object *newParent;
    // True if the object has a parent
    bool hasParent;

    // Children of the object
    std::vector<Object *> children;

    // Transform of the object
    // Global transform
    sf::Vector2f globalPosition;
    float globalRotation;
    sf::Vector2f globalScale;
    // Local transform
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;

    // True if the object is marked to be deleted (if it's true the object will be deleted at the end of the frame)
    bool toBeDeleted;
    // True if the object is marked to change its parent (if it's true the object will change it's parent at the end of the frame)
    bool toChangeParent;
    // True if the object is marked to be moved to other layer (if it's true the object will be moved at the end of the frame)
    bool toBeMoved;

    // Add a child to its list of children (Should only be called from Scene class )
    void AddChild(Object *c);
    // Remove a child from its list of children (Should only be called from Scene class)
    void RemoveChild(Object *c);

    friend class Scene;

protected:
    // Reacts to events (Should be called only from Scene class)
    virtual void OnEvent(sf::Event event);
    // Update the object each frame (Should be called only from Scene class)
    virtual void Update();
    // Draw the object (Should be called only from Scene class)
    virtual void Draw(sf::RenderWindow &window);

    // Set the active state (if it's false the update function will not be called)
    void SetActive(bool activeState);
    // Set the visibility of the object
    void SetVisible(bool visibility);

    // Changes the local position of the Object
    void SetPosition(sf::Vector2f newPosition);
    // Moves the object from it's position in a direction with a specified speed
    // dt - "Delta time" the time it took the last frame to get processed and rendered
    // Used for conversion to pixel-per-second to pixel-per frame
    void Move(sf::Vector2f direction, float speed, float dt);

    // Changes the local rotation of the Object
    void SetRotation(float newRotation);
    // Rotates the object form it's rotation twords an angle with a specified speed
    // dt - "Delta time" the time it took the last frame to get processed and rendered
    // Used for conversion to pixel-per-second to pixel-per frame
    void Rotate(float angle, float speed, float dt);
    // Changes the local scale of the Object
    void SetScale(sf::Vector2f newScale);

public:
    // Constructor
    Object();
    Object(std::string name);
    Object(int layer);
    Object(Object *parent);
    Object(std::string name, int layer);
    Object(std::string name, Object *parent);
    Object(int layer, Object *parent);
    Object(std::string name, int layer, Object *parent);

    // Deconstructor
    virtual ~Object();

    //  Get the name of the object
    std::string GetName();

    // Get the layer the object is on
    int GetLayer();

    // True if the object is registered and exists in a scene
    bool IsRegistered();

    // True if the object is active
    bool IsActive();
    // True if the drawable object is visible (always true for not drawable object -to call the function for children-)
    virtual bool IsVisible();

    // True if the object is a collider type
    virtual bool IsCollider();

    // Get the global position of the object
    sf::Vector2f GetGlobalPosition();
    // Get the global rotation of the object
    float GetGlobalRotation();
    // Get the global scale of the object
    sf::Vector2f GetGlobalScale();
    // Get the local position of the object
    sf::Vector2f GetPosition();
    // Get the local rotation of the object
    float GetRotation();
    // Get the local scale of the object
    sf::Vector2f GetScale();
    // Get the bounding rectangle of the object.
    virtual sf::FloatRect GetBounds() const;

    // True if the object is a child of another object
    bool IsChild();
    // Get the parent of the object
    Object *GetParent();
    // Return a list with the children of th parent
    const std::vector<Object *> &GetChildren();

    // Return a list of objects that are supposed to be added as children when the object is registered
    virtual const std::vector<Object *> GetChildrenToAdd();

    // Return a list with the events that the object is subscribed to
    virtual const std::vector<sf::Event::EventType> GetEventsToSubscribe();

    // True if the object is marked to be deleted
    bool IsMarkedToBeDeleted();
    // True if the object is  marked to change its parent
    bool IsMarkedToChangeParent();
    // True if the object is marked to be moved
    bool IsMarkedToBeMoved();
};

// Object that has a sprite
class SpriteObject : public Object
{
private:
    sf::Sprite sprite;
    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    // Update object each frame add changes to the sprite
    virtual void Update() override;

    // Change the source texture of the sprite.
    void SetTexture(const sf::Texture &texture, bool resetRect = false);
    // Set the sub-rectangle of the texture that the sprite will display.
    void SetTextureRect(const sf::IntRect &rectangle);

    // Set the global color of the sprite.
    void SetColor(const sf::Color &color);

    // Set the local origin of the object
    void SetOrigin(const sf::Vector2f &origin);
    // Get the local origin of the object
    const sf::Vector2f &GetOrigin() const;

public:
    SpriteObject();
    SpriteObject(std::string name);
    SpriteObject(int layer);
    SpriteObject(Object *parent);
    SpriteObject(std::string name, int layer);
    SpriteObject(std::string name, Object *parent);
    SpriteObject(int layer, Object *parent);
    SpriteObject(std::string name, int layer, Object *parent);

    // Get the source texture of the sprite.
    const sf::Texture *GetTexture() const;
    // Get the sub-rectangle of the texture displayed by the sprite.
    const sf::IntRect &GetTextureRect() const;

    // Get the global color of the sprite.
    const sf::Color &GetColor() const;

    // Get the bounding rectangle of the object.
    sf::FloatRect GetBounds() const;
};

// Object that has a text
class TextObject : public Object
{
private:
    sf::Text text;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    // Update object each frame add changes to the convex text
    virtual void Update() override;

    // Set the text's string.
    void SetString(const sf::String &string);

    // Set the text's font.
    void SetFont(const sf::Font &font);
    // Set the character size.
    void SetCharacterSize(unsigned int size);
    // Set the line spacing factor.
    void SetLineSpacing(float spacingFactor);
    // Set the letter spacing factor.
    void SetLetterSpacing(float spacingFactor);

    // Set the text's style.
    void SetStyle(sf::Uint32 style);
    // Set the fill color of the text.
    void SetFillColor(const sf::Color &color);
    // Set the outline color of the text.
    void SetOutlineColor(const sf::Color &color);
    // Set the thickness of the text's outline.
    void SetOutlineThickness(float thickness);

    // Return the position of the index-th character.
    sf::Vector2f FindCharacterPos(std::size_t index) const;

    // Set the local origin of the object
    void SetOrigin(const sf::Vector2f &origin);
    // Get the local origin of the object
    const sf::Vector2f &GetOrigin() const;

public:
    TextObject();
    TextObject(std::string name);
    TextObject(int layer);
    TextObject(Object *parent);
    TextObject(std::string name, int layer);
    TextObject(std::string name, Object *parent);
    TextObject(int layer, Object *parent);
    TextObject(std::string name, int layer, Object *parent);

    // Get the text's string.
    const sf::String &GetString() const;

    // Get the text's font.
    const sf::Font *GetFont() const;
    // Get the character size.
    unsigned int GetCharacterSize() const;
    // Get the size of the letter spacing factor.
    float GetLetterSpacing() const;
    // Get the size of the line spacing factor.
    float GetLineSpacing() const;

    // Get the text's style.
    sf::Uint32 GetStyle() const;
    // Get the fill color of the text.
    const sf::Color &GetFillColor() const;
    // Get the outline color of the text.
    const sf::Color &getOutlineColor() const;
    // Get the outline thickness of the text.
    float GetOutlineThickness() const;

    // Get the bounding rectangle of the object.
    sf::FloatRect GetBounds() const;
};

// Object that has a circle shape
class CircleObject : public Object
{
private:
    sf::CircleShape circle;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    // Update object each frame add changes to the circle
    virtual void Update() override;

    // Set the radius of the circle.
    void SetRadius(float radius);
    // Set the number of points of the circle.
    void SetPointCount(std::size_t count);
    // Get a point of the circle.
    virtual sf::Vector2f GetPoint(std::size_t index) const;

    // Change the source texture of the shape.
    void SetTexture(const sf::Texture *texture, bool resetRect = false);
    // Set the sub-rectangle of the texture that the shape will display.
    void SetTextureRect(const sf::IntRect &rectangle);

    // Set the fill color of the shape.
    void SetFillColor(const sf::Color &color);
    // Set the outline color of the shape.
    void SetOutlineColor(const sf::Color &color);
    // Set the thickness of the shape's outline.
    void setOutlineThickness(float thickness);

    // Set the local origin of the object
    void SetOrigin(const sf::Vector2f &origin);
    // Get the local origin of the object
    const sf::Vector2f &GetOrigin() const;

public:
    CircleObject();
    CircleObject(std::string name);
    CircleObject(int layer);
    CircleObject(Object *parent);
    CircleObject(std::string name, int layer);
    CircleObject(std::string name, Object *parent);
    CircleObject(int layer, Object *parent);
    CircleObject(std::string name, int layer, Object *parent);

    // Get the radius of the circle.
    float GetRadius() const;
    // Get the number of points of the circle.
    virtual std::size_t GetPointCount() const;

    // Get the source texture of the shape.
    const sf::Texture *GetTexture() const;
    // Get the sub-rectangle of the texture displayed by the shape.
    const sf::IntRect &GetTextureRect() const;

    // Get the fill color of the shape.
    const sf::Color &GetFillColor() const;
    // Get the outline color of the shape.
    const sf::Color &GetOutlineColor() const;
    // Get the outline thickness of the shape.
    float GetOutlineThickness() const;

    // Get the bounding rectangle of the object.
    sf::FloatRect GetBounds() const;
};

// Object that has a rectangle shape
class RectangleObject : public Object
{
private:
    sf::RectangleShape rectangle;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    // Update object each frame add changes to the rectangle
    virtual void Update() override;

    // Set the size of the rectangle.
    void SetSize(const sf::Vector2f &size);
    // Get a point of the shape.
    virtual sf::Vector2f GetPoint(std::size_t index) const;

    // Change the source texture of the shape.
    void SetTexture(const sf::Texture *texture, bool resetRect = false);
    // Set the sub-rectangle of the texture that the shape will display.
    void SetTextureRect(const sf::IntRect &rectangle);

    // Set the fill color of the shape.
    void SetFillColor(const sf::Color &color);
    // Set the outline color of the shape.
    void SetOutlineColor(const sf::Color &color);
    // Set the thickness of the shape's outline.
    void setOutlineThickness(float thickness);

    // Set the local origin of the object
    void SetOrigin(const sf::Vector2f &origin);
    // Get the local origin of the object
    const sf::Vector2f &GetOrigin() const;

public:
    RectangleObject();
    RectangleObject(std::string name);
    RectangleObject(int layer);
    RectangleObject(Object *parent);
    RectangleObject(std::string name, int layer);
    RectangleObject(std::string name, Object *parent);
    RectangleObject(int layer, Object *parent);
    RectangleObject(std::string name, int layer, Object *parent);

    // Get the size of the rectangle.
    const sf::Vector2f &GetSize() const;
    // Get the number of points of the shape.
    virtual std::size_t GetPointCount() const;

    // Get the source texture of the shape.
    const sf::Texture *GetTexture() const;
    // Get the sub-rectangle of the texture displayed by the shape.
    const sf::IntRect &GetTextureRect() const;

    // Get the fill color of the shape.
    const sf::Color &GetFillColor() const;
    // Get the outline color of the shape.
    const sf::Color &GetOutlineColor() const;
    // Get the outline thickness of the shape.
    float GetOutlineThickness() const;

    // Get the bounding rectangle of the object.
    sf::FloatRect GetBounds() const;
};

// Object that has a convex shape
class ConvexObject : public Object
{
private:
    sf::ConvexShape convexShape;

    // Draw the object
    void Draw(sf::RenderWindow &window) override;

protected:
    // Update object each frame add changes to the convex shape
    virtual void Update() override;

    // Set the number of points of the shape.
    void SetPointCount(std::size_t count);
    // Set the position of a point
    void SetPoint(std::size_t index, const sf::Vector2f &point);
    // Get a point of the shape.
    virtual sf::Vector2f GetPoint(std::size_t index) const;

    // Change the source texture of the shape.
    void SetTexture(const sf::Texture *texture, bool resetRect = false);
    // Set the sub-rectangle of the texture that the shape will display.
    void SetTextureRect(const sf::IntRect &rectangle);

    // Set the fill color of the shape.
    void SetFillColor(const sf::Color &color);
    // Set the outline color of the shape.
    void SetOutlineColor(const sf::Color &color);
    // Set the thickness of the shape's outline.
    void setOutlineThickness(float thickness);

    // Set the local origin of the object
    void SetOrigin(const sf::Vector2f &origin);
    // Get the local origin of the object
    const sf::Vector2f &GetOrigin() const;

public:
    ConvexObject();
    ConvexObject(std::string name);
    ConvexObject(int layer);
    ConvexObject(Object *parent);
    ConvexObject(std::string name, int layer);
    ConvexObject(std::string name, Object *parent);
    ConvexObject(int layer, Object *parent);
    ConvexObject(std::string name, int layer, Object *parent);

    // Get the number of points of the shape.
    virtual std::size_t GetPointCount() const;

    // Get the source texture of the shape.
    const sf::Texture *GetTexture() const;
    // Get the sub-rectangle of the texture displayed by the shape.
    const sf::IntRect &GetTextureRect() const;

    // Get the fill color of the shape.
    const sf::Color &GetFillColor() const;
    // Get the outline color of the shape.
    const sf::Color &GetOutlineColor() const;
    // Get the outline thickness of the shape.
    float GetOutlineThickness() const;

    // Get the bounding rectangle of the object.
    sf::FloatRect GetBounds() const;
};

// Rectangle that has the ability to collide with other objects of this class
class Collider : public RectangleObject
{
private:
    static bool showColliders;

public:
    static void ToggleDebug(bool state);
    static bool IsDebugEnabled();

    Collider();
    Collider(std::string name);
    Collider(int layer);
    Collider(Object *parent);
    Collider(std::string name, int layer);
    Collider(std::string name, Object *parent);
    Collider(int layer, Object *parent);
    Collider(std::string name, int layer, Object *parent);

    bool IsVisible() override;

    bool IsCollider() override;

    using RectangleObject::GetOrigin;
    using RectangleObject::GetPoint;
    using RectangleObject::SetOrigin;
    using RectangleObject::SetSize;
};
