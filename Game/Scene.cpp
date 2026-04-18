#include "Scene.h"

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
    for (Object *o : this->objects)
        this->RemoveObject(o);

    this->DeleteObjects(false);

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
    if (o->IsChild())
    {
        // Verify if parent exists if id doesn't remove the object
        Object *p = o->GetParent();
        if (!p)
        {
            std::cout << "Failed to add child object (Null pointer to parent)";
            delete o;
        }
        else
            p->AddChild(o);
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

    // Remove objects children and add them to the list to be deleted
    std::list<Object *> children = o->GetChildren();
    for (Object *c : children)
        this->RemoveObject(c);

    // Verify if the object is already marked to be deleted
    if (o->IsMarkedToBeDeleted())
    {
        std::cout << "Object " << o << " is already marked to be deleted" << std::endl;
        return;
    }

    // Mark the object to be deleted and add it to the list to be deleted
    o->MarkToBeDeleted();
    objectsToDelete.push_back(o);
    std::cout << "Object " << o << " added to delete list" << std::endl;
}

void Scene::DeleteObjects(bool removeFromScene)
{
    while (!this->objectsToDelete.empty())
    {
        Object *o = objectsToDelete.front();
        objectsToDelete.pop_front();

        // Verify object to exist
        if (!o)
            std::cout << "Failed to remove object (Null pointer)" << std::endl;
        else
        {
            if (removeFromScene)
            {
                // If the object is a child, it's removed from its parent
                if (o->IsChild())
                {
                    if (!o->GetParent()->IsMarkedToBeDeleted())
                        o->GetParent()->RemoveChild(o);
                }
                // If the object is not a child, it's removed from the active scene
                else
                {
                    this->objects.remove(o);
                    std::cout << "Removed object " << o << " from scene " << this << std::endl;
                }
            }

            delete o;
        }
    }
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
