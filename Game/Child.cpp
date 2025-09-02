#include "Object.h"

Child::Child(Parent *p)
{
    // Verify the parent to exist (if it doesn't it deletes itself)
    if (!p)
    {
        this->parent = nullptr;
        return;
    }

    // Sets the parent
    this->parent = p;

    this->SetActive(true);

    // Initialize local transform
    this->localPosition = sf::Vector2f(0, 0);
    this->localRotation = 0;
    this->localScale = sf::Vector2f(1, 1);
    // Initialize global transform based on parent
    this->SetPosition(this->parent->GetPosition());
    this->SetRotation(this->parent->GetRotation());
    this->SetScale(this->parent->GetScale());

    std::cout << "Child created: " << this << ", Parent: " << p << std::endl;
}

Child::Child(bool activeState, Parent *p)
{
    // Verify the parent to exist (if it doesn't it deletes itself)
    if (!p)
    {
        this->parent = nullptr;
        return;
    }

    // Sets the parent
    this->parent = p;

    this->SetActive(activeState);

    // Initialize local transform
    this->localPosition = sf::Vector2f(0, 0);
    this->localRotation = 0;
    this->localScale = sf::Vector2f(1, 1);
    // Initialize global transform based on parent
    this->SetPosition(this->parent->GetPosition());
    this->SetRotation(this->parent->GetRotation());
    this->SetScale(this->parent->GetScale());

    std::cout << "Child created: " << this << ", Parent: " << p << std::endl;
}

Child::~Child()
{
    std::cout << "Child Object destroyed " << this << std::endl;
}

void Child::SetLocalPosition(sf::Vector2f newPosition)
{
    this->localPosition = newPosition;
}

void Child::LocalMove(sf::Vector2f direction, float speed)
{
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
        direction /= magnitude;
    this->localPosition += direction * speed;
}

void Child::SetLocalRotation(float newRotation)
{
    this->localRotation = newRotation;
}

void Child::LocalRotate(float angle, float speed)
{
    this->localRotation += angle * speed;
}

void Child::SetLocalScale(sf::Vector2f newScale)
{
    this->localScale = newScale;
}

void Child::Update()
{
    // Updates the global transform based of the parent transform
    this->SetPosition(this->parent->GetPosition() + this->localPosition);
    this->SetRotation(this->parent->GetRotation() + this->localRotation);
    sf::Vector2f newScale(this->parent->GetScale().x * this->localScale.x, this->parent->GetScale().y * this->localScale.y);
    this->SetScale(newScale);
}

sf::Vector2f Child::GetLocalPosition()
{
    return this->localPosition;
}

float Child::GetLocalRotation()
{
    return this->localRotation;
}

sf::Vector2f Child::GetLocalScale()
{
    return this->localScale;
}

Parent *Child::GetParent()
{
    return this->parent;
}
