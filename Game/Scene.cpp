#include "Game.h"

SceneBuilder::SceneBuilder(sf::Vector2f cameraSize, sf::Vector2f cameraCenter, std::function<void(Scene *)> objects)
{
    this->cameraSize = cameraSize;
    this->cameraCenter = cameraCenter;
    this->addObjectsToScene = objects;
}

sf::Vector2f SceneBuilder::GetCameraSize()
{
    return this->cameraSize;
}

sf::Vector2f SceneBuilder::GetCameraCenter()
{
    return this->cameraCenter;
}

Scene::Scene(sf::Vector2f cameraSize, sf::Vector2f cameraCenter)
{
    // Initialize Camera
    this->camera.setSize(cameraSize);
    this->camera.setCenter(cameraCenter);

    std::cout << "Created scene " << this << std::endl;
}

Scene::~Scene()
{
    while (!this->objects.empty())
        RemoveObject(this->objects.back());

    std::cout << "Deleted scene " << this << std::endl;
}

std::list<Object *> Scene::GetObjects()
{
    return this->objects;
}

void Scene::AddObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to add object to scene " << this << " (NULL pointer)" << std::endl;
        return;
    }

    // If the object is a child, it's added to its parent
    Child *c = dynamic_cast<Child *>(o);
    if (c)
    {
        // Verify if parent exists if id doesn't remove the object
        Parent *p = c->GetParent();
        if (!p)
        {
            std::cout << "Failed to add child object (Null pointer to parent)";
            delete c;
        }
        else
            p->AddChild(c);
    }
    // If the object is not a child add it to the scene
    else
    {
        this->objects.push_back(o);
        std::cout << "Added object " << o << " to scene " << this << std::endl;
    }
}

void Scene::RemoveObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to remove object from scene " << this << " (NULL pointer)" << std::endl;
        return;
    }

    int l = this->objects.size();
    this->objects.remove(o);
    if (l != this->objects.size())
        std::cout << "Removed object " << o << " from scene " << this << std::endl;
}

void Scene::OnEvent(sf::Event event)
{
    for (Object *o : this->objects)
    {
        // Verify the object to exist
        if (!o)
            std::cout << "Failed to call object method (Null pointer)" << std::endl;

        else if (o->IsActive())
            o->OnEvent(event);
    }
}

void Scene::Update()
{
    for (Object *o : this->objects)
    {
        // Verify the object to exist
        if (!o)
            std::cout << "Failed to update object (Null pointer)" << std::endl;

        else if (o->IsActive())
            o->Update();
    }
}

void Scene::Draw(sf::RenderWindow *window)
{
    // Verify the window to exist
    if (!window)
    {
        std::cout << "Failed to draw scene objects (NULL pointer to window)" << std::endl;
    }

    for (Object *o : this->objects)
    {
        // Verify the object to exist
        if (!o)
            std::cout << "Failed to draw object (Null pointer)" << std::endl;

        else if (o->IsVisible())
            o->Draw(window);
    }
}
