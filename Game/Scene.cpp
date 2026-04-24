#include "Scene.h"

SceneBuilder::SceneBuilder(std::string name,
                           sf::Vector2f cameraSize, sf::Vector2f cameraCenter,
                           std::function<std::vector<Object *>()> objects)
    : name(name), cameraSize(cameraSize), cameraCenter(cameraCenter)
{
    // Initialize the variables
    this->objects = objects;
}

std::string SceneBuilder::GetName()
{
    return this->name;
}

sf::Vector2f SceneBuilder::GetCameraSize()
{
    return this->cameraSize;
}

sf::Vector2f SceneBuilder::GetCameraCenter()
{
    return this->cameraCenter;
}

void Scene::SubscribeToEvents(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to subscribe object to events (NULL pointer)" << std::endl;
        return;
    }

    // Get the events that the object is subscribed to
    const std::vector<sf::Event::EventType> events = o->GetEventsToSubscribe();

    // Subscribe the object to the events
    for (sf::Event::EventType event : events)
    {
        this->eventSubscribers[event].push_back(o);
        std::cout << "Subscribed: " << o->name << '-' << o
                  << " to event: " << event << std::endl;
    }
}

void Scene::UnsubscribeFromEvents(Object *o)
{
    if (!o)
    {
        std::cout << "Failed to unsubscribe object from events (NULL pointer)" << std::endl;
        return;
    }

    // Get the events that the object is subscribed to
    const std::vector<sf::Event::EventType> events = o->GetEventsToSubscribe();

    // Unsubscribe the object from the events
    for (sf::Event::EventType event : events)
    {
        // Find the object in the list of subscribers for the event and verify it to exist
        auto it = std::find(this->eventSubscribers[event].begin(), this->eventSubscribers[event].end(), o);
        if (it == this->eventSubscribers[event].end())
        {
            std::cout << "Failed to unsubscribe: " << o->name << '-' << o
                      << " from event: " << event
                      << " (Not found in subscribers list)" << std::endl;
            continue;
        }

        // Remove the object from the list of subscribers for the event
        *it = this->eventSubscribers[event].back();
        this->eventSubscribers[event].pop_back();
        std::cout << "Unsubscribed: " << o->name << '-' << o
                  << " from event: " << event << std::endl;
    }
}

Scene::Scene(std::string name, sf::Vector2f cameraSize, sf::Vector2f cameraCenter) : name(name)
{
    // Initialize Camera
    this->camera.setSize(cameraSize);
    this->camera.setCenter(cameraCenter);

    std::cout << "Created: " << this->name << '-' << this << std::endl;
}

Scene::~Scene()
{
    // Mark all objects to be deleted and add them to the list to be deleted
    for (auto layer : layers)
        for (Object *o : layer.second)
            this->RemoveObject(o);

    // Delete the objects that are marked to be deleted
    this->DeleteObjects(false);

    std::cout << "Deleted: " << this->name << '-' << this << std::endl;
}

std::string Scene::GetName()
{
    return this->name;
}

void Scene::AddObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to add object to: " << this->name << '-' << this
                  << " objects list (NULL pointer)" << std::endl;
        return;
    }

    if (o->registered)
    {
        std::cout << "Failed to add: " << o->name << '-' << o
                  << " to: " << this->name << '-' << this
                  << " objects list (Already registered)" << std::endl;
        return;
    }

    // Verify the object is a child
    if (o->hasParent && o->parent != nullptr)
    {
        // Ensure the object has the same layer sa its parent
        Object *p = o->parent;
        if (p->layer != o->layer)
            std::cout << o->name << '-' << o
                      << " cannot be on a different layer than its parent: " << p->name << '-' << p
                      << " Setting layer from: " << o->layer
                      << " to: " << p->layer << std::endl;
        o->layer = p->layer;
    }
    // If the object is not a child add it to the scene
    else
    {
        // If the object was marked ass a child but it dose not have a parent mark it as a root object
        if (o->hasParent)
        {
            std::cout << "Failed to add: " << o->name << '-' << o
                      << " to children list (NULL pointer to parent) - Adding to scene instead";

            o->hasParent = false;
        }

        // Add the object to the scene
        this->layers[o->layer].push_back(o);
        std::cout << "Added: " << o->name << '-' << o
                  << " to: " << this->name << '-' << this
                  << " objects list-layer: " << o->layer << std::endl;
    }

    // Subscribe the object to the events that it wants to react to
    this->SubscribeToEvents(o);

    // Register all of the children
    const std::vector<Object *> &children = o->GetChildren();
    for (Object *c : children)
        this->AddObject(c);

    // Mark the object as registered
    o->registered = true;
}

void Scene::RemoveObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to remove object from: " << this->name << '-' << this
                  << " (NULL pointer)" << std::endl;
        return;
    }

    // Remove objects children and add them to the list to be deleted
    const std::vector<Object *> &children = o->GetChildren();
    for (Object *c : children)
        this->RemoveObject(c);

    // Verify if the object is already marked to be deleted
    if (o->toBeDeleted)
    {
        std::cout << "Failed to add: " << o->name << '-' << o
                  << " to delete list (Already marked to be deleted)" << std::endl;
        return;
    }

    // Mark the object to be deleted
    o->toBeDeleted = true;
    // Add the object to the delete list
    this->objectsToDelete.push_back(o);
    std::cout << "Added: " << o->name << '-' << o
              << " to delete list" << std::endl;
}

void Scene::DeleteObjects(bool removeFromScene)
{
    for (int i = 0; i < objectsToDelete.size(); i++)
    {
        // Get the object to be deleted and set the pointer to null in the list
        Object *o = objectsToDelete.at(i);
        objectsToDelete[i] = nullptr;

        // Verify object to exist
        if (!o)
        {
            std::cout << "Failed to delete object (NULL pointer)" << std::endl;
            continue;
        }

        if (removeFromScene)
        {
            // If the object is a child, it's removed from its parent
            if (o->hasParent)
            {
                // Verify if parent exists
                Object *p = o->parent;
                if (!p)
                {
                    std::cout << "Failed to remove: " << o->name << '-' << o
                              << " from children list (NULL pointer to parent)" << std::endl;
                    delete o;
                    continue;
                }

                // If the parent is not marked to be deleted, the child is removed from the parent
                if (!p->toBeDeleted)
                    p->RemoveChild(o);
            }
            // If the object is not a child, it's removed from the active scene
            else
            {
                // Find the object in the scene and verify it to exist
                int l = o->layer;
                auto it = std::find(this->layers[l].begin(), this->layers[l].end(), o);
                if (it == this->layers[l].end())
                {
                    std::cout << "Failed to remove: " << o->name << '-' << o
                              << " from: " << this->name << '-' << this
                              << " objects list-layer: " << l
                              << " (Not found in list)" << std::endl;
                    delete o;
                    continue;
                }

                // Remove the object from the scene
                *it = this->layers[l].back();
                this->layers[l].pop_back();
                std::cout << "Removed: " << o->name << '-' << o
                          << " from: " << this->name << '-' << this
                          << " objects list-layer: " << l << std::endl;
            }

            // Unsubscribe the object from the events that it was subscribed to
            this->UnsubscribeFromEvents(o);
        }

        delete o;
    }

    objectsToDelete.clear();
}

void Scene::SetObjectLayer(int layer, Object *o)
{
    if (!o)
    {
        std::cout << "Failed to set layer of object (NULL pointer)" << std::endl;
        return;
    }

    if (o->layer == layer)
    {
        std::cout << "Failed to set layer of: " << o->name << o
                  << "(Already on layer: " << layer << ")" << std::endl;
        return;
    }

    // Verify if the object is a child (if it is its layer must be its parents layer)
    if (o->hasParent)
    {
        Object *p = o->parent;
        if (!p)
        {
            std::cout << "Failed to set layer of: " << o->name << '-' << o
                      << " (NULL pointer to parent)" << std::endl;
            return;
        }
        if (p->layer != layer)
        {
            std::cout << "Failed to set layer of: " << o->name << '-' << o
                      << " (Cannot be on a different layer than its parent: " << p->name << '-' << p
                      << ") Remaining on layer: " << p->layer << std::endl;
            return;
        }
    }
    // If it isn't a child verify it not to be already marked to be moved
    else if (o->toBeMoved)
    {
        std::cout << "Failed to set layer of: " << o->name << '-' << o
                  << " (Already marked to be moved to layer: " << o->layer << ")" << std::endl;
        return;
    }
    // If it isn't mark it to be moved
    else
    {
        o->toBeMoved = true;
        this->objectsToMove.push_back(o);
    }

    // Set it's layer and save the old layer so it can be removed from that one
    o->oldLayer = o->layer;
    o->layer = layer;

    std::cout << "Setted: " << o->name << '-' << o
              << " layer from: " << o->oldLayer
              << " to: " << o->layer << std::endl;

    // Set the layer for it's children
    const std::vector<Object *> &children = o->GetChildren();
    for (Object *c : children)
        SetObjectLayer(layer, c);
}

void Scene::MoveObjects()
{
    for (int i = 0; i < objectsToMove.size(); i++)
    {
        // Get the object to be moved and set the pointer tu null in the list
        Object *o = objectsToMove.at(i);
        objectsToMove[i] = nullptr;

        // Verify the object to exist
        if (!o)
        {
            std::cout << "Failed to move object (NULL pointer)";
            continue;
        }

        // Search for the object in the old layer
        int ol = o->oldLayer, l = o->layer;
        auto it = std::find(this->layers[ol].begin(), this->layers[ol].end(), o);
        if (it == this->layers[ol].end())
        {
            std::cout << "Failed to move: " << o->name << '-' << o
                      << " from: " << this->name << '-' << this
                      << " layer: " << ol << " to layer: " << l
                      << " (Not found in list)";

            // Add the object to the new layer
            this->layers[l].push_back(o);

            o->toBeMoved = false;

            std::cout << "Added: " << o->name << '-' << o
                      << " to: " << this->name << '-' << this
                      << " layer: " << l << std::endl;
            continue;
        }

        // Remove the object from the old layer
        *it = this->layers[ol].back();
        this->layers[ol].pop_back();

        // Add the object to the new layer
        this->layers[l].push_back(o);

        o->toBeMoved = false;

        std::cout << "Moved: " << o->name << '-' << o
                  << " from: " << this->name << '-' << this
                  << " layer: " << ol << " to layer: " << l << std::endl;
    }

    objectsToMove.clear();
}

void Scene::OnEvent(sf::Event event)
{
    for (Object *o : this->eventSubscribers[event.type])
    {
        // Verify the object to exist
        if (!o)
        {
            std::cout << "Failed to call object OnEvent() (NULL pointer)" << std::endl;
            continue;
        }

        if (!o->active)
            continue;

        if (o->hasParent)
        {
            bool active = true;
            Object *aux = o;
            do
            {
                // Verify if parent exists
                Object *p = aux->parent;
                if (!p)
                {
                    std::cout << "Failed to call: " << o->name << '-' << o << " OnEvent() (NULL pointer to parent)" << std::endl;
                    active = false;
                }
                else
                {
                    active = p->active;
                    aux = p;
                }

            } while (aux->hasParent && active);

            if (!active)
                continue;
        }

        o->OnEvent(event);
    }
}

void Scene::Update()
{
    for (auto objects : layers)
        for (Object *o : objects.second)
        {
            // Verify the object to exist
            if (!o)
            {
                std::cout << "Failed to update object (NULL pointer)" << std::endl;
                continue;
            }

            if (o->active)
                o->Update();
        }
}

void Scene::Draw(sf::RenderWindow &window)
{
    for (auto objects : layers)
        for (Object *o : objects.second)
        {
            // Verify the object to exist
            if (!o)
            {
                std::cout << "Failed to draw object (NULL pointer)" << std::endl;
                continue;
            }

            if (o->visible)
                o->Draw(window);
        }
}

SceneManager::SceneManager()
{
    // Initialize the variables
    this->activeScene = nullptr;
    this->nextScene = nullptr;
    this->changingScene = false;
}

SceneManager::~SceneManager()
{
    // Delete the active and next scene if they exist
    if (this->nextScene)
        delete this->nextScene;
    if (this->activeScene)
        delete this->activeScene;
}

void SceneManager::ChangeScene(SceneBuilder s)
{
    // If there is already a next scene scheduled, delete it to prevent memory leaks
    if (this->nextScene)
        delete this->nextScene;

    // Creates the scene
    this->nextScene = new Scene(s.GetName(), s.GetCameraSize(), s.GetCameraCenter());
    // Creates and adds the objects to the scene
    std::vector<Object *> obj = s.objects();
    for (auto o : obj)
        nextScene->AddObject(o);

    // Sets the flag to change the scene when the Update() and Run() methods are over
    this->changingScene = true;
}

void SceneManager::SetActiveScene()
{
    // If the scene is not scheduled to change, do nothing
    if (!this->changingScene)
        return;

    // Verify the next scene to exist
    if (!nextScene)
    {
        std::cout << "Failed to set scene (NULL pointer)" << std::endl;
        return;
    }

    // Changes the scene
    Scene *previousScene = this->activeScene;
    this->activeScene = nextScene;

    // Sets the flag to stop the changing
    nextScene = nullptr;
    this->changingScene = false;

    std::cout << "Active scene is set to: "
              << activeScene->name << '-' << activeScene << std::endl;

    // Deletes the previous scene if it exists
    if (previousScene)
        delete previousScene;
}

void SceneManager::AddObject(Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to add object to active scene (NULL pointer to scene)" << std::endl;
        return;
    }

    // Add to the active scene
    this->activeScene->AddObject(o);
}

void SceneManager::RemoveObject(Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to remove object from active scene (NULL pointer to scene)" << std::endl;
        return;
    }

    this->activeScene->RemoveObject(o);
}

void SceneManager::SetObjectLayer(int layer, Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to set objects layer in active scene (NULL pointer to scene)" << std::endl;
        return;
    }

    this->activeScene->SetObjectLayer(layer, o);
}

void SceneManager::DeleteObjects()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to delete marked objects in active scene (NULL pointer to scene)" << std::endl;
        return;
    }

    this->activeScene->DeleteObjects();
}

void SceneManager::MoveObjects()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to move marked objects is active scene (NULL pointer to scene)" << std::endl;
        return;
    }

    this->activeScene->MoveObjects();
}

void SceneManager::OnEvent(sf::Event event)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to react to events from active scene's objects (NULL pointer to scene)" << std::endl;
        return;
    }

    // If the active scene exists, react to events from its objects
    this->activeScene->OnEvent(event);
}

void SceneManager::Update()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to update scene objects (NULL pointer to scene)" << std::endl;
        return;
    }

    // Update all active objects in the active scene
    this->activeScene->Update();
}

void SceneManager::Draw(sf::RenderWindow &window)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to draw scene objects (NULL pointer to scene)" << std::endl;
        return;
    }

    // Update the view of the window
    window.setView(this->activeScene->camera);

    // Draws all the visible objects in the active scene
    this->activeScene->Draw(window);
}

sf::View &SceneManager::GetCamera()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to get active scene camera (NULL pointer to scene)" << std::endl;
        return this->defaultCamera;
    }

    return this->activeScene->camera;
}
