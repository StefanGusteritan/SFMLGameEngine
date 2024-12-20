#include "Object.h"

void Parent::Delete()
{
    while (!this->children.empty())
        this->children.back()->Delete();
    std::cout << "Parent Object destroyed" << this << std::endl;
    delete this;
}

void Parent::AddChild(Object *c)
{
    if (!c)
    {
        std::cout << "Failed to add child (Null pointer)" << std::endl;
        return;
    }

    std::cout << "Adding child " << c << " to " << this << " children list" << std::endl;
    this->children.push_back(c);
}

void Parent::RemoveChild(Object *c)
{
    if (!c)
    {
        std::cout << "Failed to remove child (Null pointer)" << std::endl;
        return;
    }

    std::cout << "Removing child" << c << " from " << this << " children list" << std::endl;
    this->children.remove(c);
}
