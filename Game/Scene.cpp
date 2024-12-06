#include "Game.h"

Scene::Scene()
{
    std::cout << "Created scene " << this << std::endl;
}

Scene::~Scene()
{
    while (!this->objects.empty())
        RemoveObject(this->objects.back());

    std::cout << "Deleted scene " << this << std::endl;
}

void Scene::AddObject(Object *o)
{
    if (!o)
    {
        std::cout << "Failed to add object to scene " << this << " (NULL pointer)" << std::endl;
        return;
    }

    this->objects.push_back(o);
    std::cout << "Added object " << o << " to scene " << this << std::endl;
}

void Scene::RemoveObject(Object *o)
{
    if (!o)
    {
        std::cout << "Failed to remove object from scene " << this << " (NULL pointer)" << std::endl;
        return;
    }

    this->objects.remove(o);
    std::cout << "Removed object " << o << " from scene " << this << std::endl;
    o->Delete();
}

void Scene::Update()
{
    for (Object *o : this->objects)
        if (o->IsActive())
            o->Update();
}

void Scene::Draw(sf::RenderWindow *window)
{
    if (!window)
    {
        std::cout << "Failed to draw scene objects (NULL pointer to window)" << std::endl;
    }

    for (Object *o : this->objects)
    {
        SpriteObject *so = dynamic_cast<SpriteObject *>(o);
        TextObject *to = dynamic_cast<TextObject *>(o);
        CircleObject *co = dynamic_cast<CircleObject *>(o);
        RectangleObject *ro = dynamic_cast<RectangleObject *>(o);
        ConvexObject *cvo = dynamic_cast<ConvexObject *>(o);

        if (so)
        {
            if (so->IsVisible())
                window->draw(so->GetSprite());
        }
        else if (to)
        {
            if (to->IsVisible())
                window->draw(to->GetText());
        }
        else if (co)
        {
            if (co->IsVisible())
                window->draw(co->GetCircleShape());
        }
        else if (ro)
        {
            if (ro->IsVisible())
                window->draw(ro->GetRectangleShape());
        }
        else if (cvo)
        {
            if (cvo->IsVisible())
                window->draw(cvo->GetConvexShape());
        }
        else if (!o)
            std::cout << "Failed to draw object (Null pointer)" << std::endl;
    }
}
