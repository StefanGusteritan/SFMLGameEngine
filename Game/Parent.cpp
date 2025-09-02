#include "Object.h"

Parent::~Parent()
{
    std::cout << "Parent Object destroyed " << this << std::endl;
}

std::list<Object *> Parent::GetChildren()
{
    return this->children;
}

void Parent::AddChild(Object *c)
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

void Parent::RemoveChild(Object *c)
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

void Parent::OnEvent(sf::Event event)
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

void Parent::Update()
{
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
            std::cout << "Failed to update child (Null pointer)" << std::endl;

        else if (c->IsActive())
            c->Update();
    }
}

void Parent::Draw(sf::RenderWindow *window)
{
    for (auto c : this->children)
    {
        // Verify the child to exist
        if (!c)
            std::cout << "Failed to draw child (Null pointer)" << std::endl;

        else if (c->IsVisible())
            c->Draw(window);
    }
}
