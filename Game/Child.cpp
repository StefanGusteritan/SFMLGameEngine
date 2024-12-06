#include "Object.h"

Child::Child(Parent *p)
{
    if (!p)
    {
        std::cout << "Failed to create child object (Null pinter to parent)" << std::endl;
        delete this;
    }

    this->active = true;

    this->parent = p;
    this->parent->AddChild(this);

    // Initialize transform based on parent
    this->position = this->parent->GetPosition();
    this->rotation = this->parent->GetRotation();
    this->scale = this->parent->GetScale();

    // Initialize local transform
    this->localPosition = sf::Vector2f(0, 0);
    this->localRotation = 0;
    this->localScale = sf::Vector2f(1, 1);

    std::cout << "Child created: " << this << ", Parent: " << p << std::endl;
}

Child::Child(bool activeState, Parent *p)
{
    if (!p)
    {
        std::cout << "Failed to create child object (Null pinter to parent)" << std::endl;
        delete this;
    }

    this->active = activeState;

    this->parent = p;
    this->parent->AddChild(this);

    // Initialize transform based on parent
    this->position = this->parent->GetPosition();
    this->rotation = this->parent->GetRotation();
    this->scale = this->parent->GetScale();

    // Initialize local transform
    this->localPosition = sf::Vector2f(0, 0);
    this->localRotation = 0;
    this->localScale = sf::Vector2f(1, 1);

    std::cout << "Child created: " << this << ", Parent: " << p << std::endl;
}

void Child::Delete()
{
    if (this->parent)
        this->parent->RemoveChild(this);
    std::cout << "Child Object destroyed" << this << std::endl;
    delete this;
}

bool Child::IsActive()
{
    return this->parent->IsActive() && this->active;
}

void Child::Update()
{
    this->SetPosition(this->parent->GetPosition() + this->localPosition);
    this->SetRotation(this->parent->GetRotation() + this->localRotation);
    sf::Vector2f newScale(this->parent->GetScale().x * this->localScale.x, this->parent->GetScale().y * this->localScale.y);
    this->SetScale(newScale);
}
