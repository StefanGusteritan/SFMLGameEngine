#include "Object.h"

Parent::~Parent()
{
    std::cout << "Deleting Object" << this << std::endl;
    while (!this->children.empty())
        delete this->children.back();
}

void Parent::AddChild(Child *c)
{
    if (!c)
    {
        std::cout << "Failed to add child (Null pointer)" << std::endl;
        return;
    }

    std::cout << "Adding child" << c << " to " << this << " children list" << std::endl;
    this->children.push_back(c);
}

void Parent::RemoveChild(Child *c)
{
    if (!c)
    {
        std::cout << "Failed to remove child (Null pointer)" << std::endl;
        return;
    }

    std::cout << "Removing child" << c << " from " << this << " children list" << std::endl;
    this->children.remove(c);
}
