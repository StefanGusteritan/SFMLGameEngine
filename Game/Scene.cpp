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

Scene::Scene(std::string name, sf::Vector2f cameraSize, sf::Vector2f cameraCenter) : name(name)
{
    // Initialize Camera
    this->camera.setSize(cameraSize);
    this->camera.setCenter(cameraCenter);

    LOG("Created: " << this->name << '-' << this);
}

Scene::~Scene()
{
    // Mark all objects to be deleted and add them to the list to be deleted
    for (auto layer : layers)
        for (Object *o : layer.second)
            this->RemoveObject(o);

    // Delete the objects that are marked to be deleted
    this->DeleteObjects(false);

    this->layers.clear();
    this->objectsToDelete.clear();
    this->objectsToChangeParent.clear();
    this->objectsToMove.clear();
    this->camera = sf::View();
    this->eventSubscribers.clear();
    this->colliders.clear();

    LOG("Deleted: " << this->name << '-' << this);
}

std::string Scene::GetName()
{
    return this->name;
}

void Scene::SubscribeToEvents(Object *o)
{
    // Verify the object to exist
    if (!o || !o->IsRegistered())
    {
        LOG_ERR("Failed to subscribe object to events (NULL pointer or not registered)");
        return;
    }

    // Get the events that the object is subscribed to
    const std::vector<sf::Event::EventType> events = o->GetEventsToSubscribe();

    // Subscribe the object to the events
    for (sf::Event::EventType event : events)
    {
        this->eventSubscribers[event].push_back(o);
        o->subscriberIndices[event] = this->eventSubscribers[event].size() - 1;
        LOG("Subscribed: " << o->name << '-' << o
                           << " to event: " << event);
    }
}

void Scene::UnsubscribeFromEvents(Object *o)
{
    if (!o || !o->IsRegistered())
    {
        LOG_ERR("Failed to unsubscribe object from events (NULL pointer or not registered)");
        return;
    }

    // Get the events that the object is subscribed to
    const std::vector<sf::Event::EventType> events = o->GetEventsToSubscribe();

    // Unsubscribe the object from the events
    for (sf::Event::EventType event : events)
    {
        // Verify object is in subscribers list
        auto it = o->subscriberIndices.find(event);
        if (it == o->subscriberIndices.end())
        {
            LOG_ERR("Failed to unsubscribe: " << o->name << '-' << o
                                              << " from event: " << event
                                              << " (Not found in subscribers list)");
            continue;
        }

        size_t index = it->second;
        auto &subs = this->eventSubscribers[event];
        if (!(index < subs.size() && subs[index] == o))
        {
            LOG_ERR("Failed to unsubscribe: " << o->name << '-' << o
                                              << " from event: " << event
                                              << " (Not found in subscribers list)");
            continue;
        }

        // Remove the object from the list of subscribers for the event
        if (subs.at(index) != subs.back())
        {
            subs.at(index) = subs.back();
            subs.at(index)->subscriberIndices[event] = index;
        }
        subs.pop_back();
        o->subscriberIndices.erase(event);
        LOG("Unsubscribed: " << o->name << '-' << o
                             << " from event: " << event);
    }
}

void Scene::AddObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        LOG_ERR("Failed to add object to: " << this->name << '-' << this
                                            << " objects list (NULL pointer)");
        return;
    }

    if (o->registered)
    {
        LOG_ERR("Failed to add: " << o->name << '-' << o
                                  << " to: " << this->name << '-' << this
                                  << " objects list (Already registered)");
        return;
    }

    // Verify the object is a child
    if (o->hasParent && o->parent != nullptr)
    {
        // Ensure the object has the same layer sa its parent
        Object *p = o->parent;

        // Add the object to its parent children list
        p->AddChild(o);

        if (p->layer != o->layer)
            LOG(o->name << '-' << o
                        << " cannot be on a different layer than its parent: " << p->name << '-' << p
                        << " Setting layer from: " << o->layer
                        << " to: " << p->layer);
        o->layer = p->layer;
    }
    // If the object is not a child add it to the scene
    else
    {
        // If the object was marked ass a child but it dose not have a parent mark it as a root object
        if (o->hasParent)
        {
            LOG_ERR("Failed to add: " << o->name << '-' << o
                                      << " to children list (NULL pointer to parent) - Adding to scene instead");

            o->hasParent = false;
        }

        // Add the object to the scene
        this->layers[o->layer].push_back(o);
        o->objectIndex = this->layers[o->layer].size() - 1;
        LOG("Added: " << o->name << '-' << o
                      << " to: " << this->name << '-' << this
                      << " objects list-layer: " << o->layer);
    }

    // If the object is a collider add it to the list of colliders
    if (o->IsCollider())
    {
        this->colliders.push_back(o);
        o->colliderIndex = this->colliders.size() - 1;
        LOG("Added: " << o->name << '-' << o
                      << " to: " << this->name << '-' << this
                      << " colliders list");
    }

    // Mark the object as registered
    o->registered = true;

    // Register all of the children
    const std::vector<Object *> children = o->GetChildrenToAdd();
    for (Object *c : children)
        this->AddObject(c);

    // Subscribe the object to the events that it wants to react to
    this->SubscribeToEvents(o);
}

void Scene::RemoveObject(Object *o)
{
    // Verify the object to exist
    if (!o || !o->IsRegistered())
    {
        LOG_ERR("Failed to remove object from: " << this->name << '-' << this
                                                 << " (NULL pointer or not registered)");
        return;
    }

    // Verify if the object is already marked to be deleted
    if (o->toBeDeleted)
    {
        LOG_ERR("Failed to mark: " << o->name << '-' << o
                                   << " to be deleted (Already marked to be deleted)");
        return;
    }

    // Mark the object to be deleted
    o->toBeDeleted = true;
    // Add the object to the delete list
    this->objectsToDelete.push_back(o);
    LOG("Marked: " << o->name << '-' << o
                   << " to be deleted");
}

void Scene::DeleteObjects(bool removeFromScene)
{
    // Unmark all the objects that have ancestors also marked to prevent double delete
    for (int i = 0; i < objectsToDelete.size(); i++)
    {
        Object *o = objectsToDelete.at(i);

        if (!o || !o->IsRegistered())
            continue;

        Object *p = o->parent;
        while (p && !p->toBeDeleted)
            p = p->parent;
        if (p && p->IsRegistered())
        {
            LOG_ERR("Failed to delete: " << o->name << '-' << o
                                         << " (Will be deleted with its ancestor: " << p << ")");
            objectsToDelete[i] = nullptr;
        }
    }

    for (int i = 0; i < objectsToDelete.size(); i++)
    {
        // Get the object to be deleted and set the pointer to null in the list
        Object *o = objectsToDelete.at(i);
        objectsToDelete[i] = nullptr;

        // Verify object to exist
        if (!o || !o->IsRegistered())
            continue;

        // Delete objects children and all of their children
        std::vector<Object *> allChildren = o->GetChildren();
        for (int j = 0; j < allChildren.size(); j++)
        {
            Object *c = allChildren.at(j);
            allChildren[j] = nullptr;

            if (!c || !c->IsRegistered())
                continue;

            const std::vector<Object *> &children = c->GetChildren();
            allChildren.insert(allChildren.end(), children.begin(), children.end());
            c->children.clear();

            if (removeFromScene)
            {
                this->UnsubscribeFromEvents(c);

                if (c->IsCollider())
                {
                    size_t index = c->colliderIndex;
                    if (!(index < this->colliders.size() && this->colliders[index] == c))
                    {
                        LOG_ERR("Failed to remove: " << c->name << '-' << c
                                                     << " from: " << this->name << '-' << this
                                                     << " colliders list (Not found in list)");
                    }
                    else
                    {
                        this->colliders.at(index) = this->colliders.back();
                        this->colliders.at(index)->colliderIndex = index;
                        this->colliders.pop_back();
                    }
                }
            }

            delete c;
        }
        allChildren.clear();
        o->children.clear();

        if (removeFromScene)
        {

            // If the object is a child, it's removed from its parent
            if (o->hasParent)
            {
                // Verify if parent exists
                Object *p = o->parent;
                if (!p || !p->IsRegistered())
                {
                    LOG_ERR("Failed to remove: " << o->name << '-' << o
                                                 << " from children list (NULL pointer to parent or not registered parent)");

                    // Unsubscribe the object from the events that it was subscribed to
                    this->UnsubscribeFromEvents(o);

                    delete o;
                    continue;
                }

                // If the parent is not marked to be deleted, the child is removed from the parent
                p->RemoveChild(o);
            }
            // If the object is not a child, it's removed from the active scene
            else
            {
                // Verify the object to be in its layer
                int l = o->layer;
                auto &layer = this->layers[l];
                size_t index = o->objectIndex;
                if (!(index < layer.size() && layer[index] == o))
                {
                    LOG_ERR("Failed to remove: " << o->name << '-' << o
                                                 << " from: " << this->name << '-' << this
                                                 << " objects list-layer: " << l
                                                 << " (Not found in list)");

                    // Unsubscribe the object from the events that it was subscribed to
                    this->UnsubscribeFromEvents(o);

                    delete o;
                    continue;
                }

                // Remove the object from the scene
                layer.at(index) = layer.back();
                layer.at(index)->objectIndex = index;
                layer.pop_back();
                LOG("Removed: " << o->name << '-' << o
                                << " from: " << this->name << '-' << this
                                << " objects list-layer: " << l);
            }

            if (o->IsCollider())
            {
                size_t index = o->colliderIndex;
                if (!(index < this->colliders.size() && this->colliders[index] == o))
                {
                    LOG_ERR("Failed to remove: " << o->name << '-' << o
                                                 << " from: " << this->name << '-' << this
                                                 << " colliders list (Not found in list)");
                }
                else
                {
                    this->colliders.at(index) = this->colliders.back();
                    this->colliders.at(index)->colliderIndex = index;
                    this->colliders.pop_back();
                }
            }

            // Unsubscribe the object from the events that it was subscribed to
            this->UnsubscribeFromEvents(o);
        }

        delete o;
    }

    objectsToDelete.clear();
}

void Scene::SetObjectParent(Object *p, Object *o)
{
    // Verify the object to exist
    if (!o || !o->IsRegistered())
    {
        LOG_ERR("Failed to set objects parent (NULL pointer or not registered)");
        return;
    }

    if (p && !p->IsRegistered())
    {
        LOG_ERR("Failed to set: " << o->name << '-' << o
                                  << " parent (Parent not registered)");
        return;
    }

    // Verify the object not to be already marked to change parent
    if (o->toChangeParent)
    {
        if (!p)
        {
            LOG_ERR("Failed to set: " << o->name << '-' << o
                                      << " parent to: (No parent)"
                                      << " (Already marked to change parent)");
        }
        else
        {
            LOG_ERR("Failed to set: " << o->name << '-' << o
                                      << " parent to: " << p->name << '-' << p
                                      << " (Already marked to change parent)");
        }
        return;
    }

    // Verify the new parent to be different from the old one
    if (o->parent == p)
    {
        if (!p)
        {
            LOG_ERR("Failed to set: " << o->name << '-' << o
                                      << " parent (Already has this parent: (No parent))");
        }
        else
        {
            LOG_ERR("Failed to set: " << o->name << '-' << o
                                      << " parent (Already has this parent: " << p->name << '-' << p << ')');
        }
        return;
    }

    // Mark the object to change parent
    o->toChangeParent = true;
    this->objectsToChangeParent.push_back(o);

    // Set the new parent to change to
    o->newParent = p;

    if (o->hasParent && o->parent->IsRegistered())
    {
        if (p)
        {
            LOG("Marked: " << o->name << '-' << o
                           << " to change parent from: " << o->parent->name << '-' << o->parent
                           << " to: " << p->name << '-' << p);
        }
        else
        {
            LOG("Marked: " << o->name << '-' << o
                           << " to change parent from: " << o->parent->name << '-' << o->parent
                           << " to: (No parent)");
        }
    }
    else
    {
        LOG("Marked: " << o->name << '-' << o
                       << " to change parent from: (No parent)"
                       << " to: " << p->name << '-' << p);
    }
}

void Scene::ChangeParents()
{
    for (int i = 0; i < this->objectsToChangeParent.size(); i++)
    {
        // Get the object to change its parent and set the pointer tu null in the list
        Object *o = objectsToChangeParent.at(i);
        objectsToChangeParent[i] = nullptr;

        // Verify the object to exist
        if (!o || !o->IsRegistered())
        {
            LOG_ERR("Failed to change objects parent (NULL pointer or not registered)");
            continue;
        }

        if (o->newParent && !o->newParent->IsRegistered())
        {
            o->newParent = nullptr;
            o->toChangeParent = false;
            LOG_ERR("Failed to change objects parent (NULL pointer or not registered)");
            continue;
        }

        // Verify the new parent isn't the object's descendant
        Object *np = o->newParent;
        while (np && np != o)
            np = np->parent;
        if (np)
        {
            LOG_ERR("Failed to change: " << o->name << '-' << o
                                         << " parent to: " << o->newParent->name << '-' << o->newParent
                                         << " (Cannot have its own descendant as its parent)");
            o->newParent = nullptr;
            o->toChangeParent = false;
            continue;
        }
        np = nullptr;

        int l = o->layer;
        Object *op = o->parent, *p = o->newParent;
        o->parent = p;
        o->hasParent = (p != nullptr);
        o->newParent = nullptr;
        o->toChangeParent = false;

        // If the old parent exists remove the object from it
        if (op && op->IsRegistered())
            op->RemoveChild(o);
        // If the old parent doesn't exist remove the object from the layer
        else
        {
            // Verify if the object is in its layer
            size_t index = o->objectIndex;
            auto &layer = this->layers[l];
            if (!(index < layer.size() && layer[index] == o))
            {
                LOG_ERR("Failed to remove: " << o->name << '-' << o
                                             << " from: " << this->name << '-' << this
                                             << " layer: " << l);
            }
            else
            {
                // Remove the object from the layer
                layer.at(index) = layer.back();
                layer.at(index)->objectIndex = index;
                layer.pop_back();
            }
        }

        // If the new parent exists add the object to its list of children
        if (p)
        {
            p->AddChild(o);

            // Make objects layer match its new parent
            if (o->layer != p->layer)
            {
                o->layer = p->layer;
                LOG("Moved: " << o->name << '-' << o
                              << " from: " << this->name << '-' << this
                              << " layer: " << l
                              << " to its new parent's layer: " << o->layer);

                // Move all objects children and all of their children
                std::vector<Object *> allChildren = o->GetChildren();
                for (int j = 0; j < allChildren.size(); j++)
                {
                    Object *c = allChildren.at(j);

                    if (!c || !c->IsRegistered())
                        continue;

                    const std::vector<Object *> &children = c->GetChildren();
                    allChildren.insert(allChildren.end(), children.begin(), children.end());

                    c->layer = o->layer;
                    LOG("Moved: " << c->name << '-' << c
                                  << " from: " << this->name << '-' << this
                                  << " layer: " << l
                                  << " to its new parent's layer: " << c->layer);
                }
                allChildren.clear();
            }
        }
        // If the new parent doesn't exist add the object to its layer
        else
        {
            // Add the object to the new layer
            this->layers[l].push_back(o);
            o->objectIndex = this->layers[l].size() - 1;

            LOG("Added: " << o->name << '-' << o
                          << " to: " << this->name << '-' << this
                          << " layer: " << l);
        }
    }

    this->objectsToChangeParent.clear();
}

void Scene::SetObjectLayer(int layer, Object *o)
{
    // Verify the object to exist
    if (!o || !o->IsRegistered())
    {
        LOG_ERR("Failed to set layer of object (NULL pointer or not registered)");
        return;
    }

    // Verify it not to be already marked to be moved
    if (o->toBeMoved)
    {
        LOG_ERR("Failed to set layer of: " << o->name << '-' << o
                                           << " (Already marked to be moved to layer: " << o->layer << ")");
        return;
    }

    // Verify the new layer is different from the old one
    if (o->layer == layer)
    {
        LOG_ERR("Failed to set layer of: " << o->name << '-' << o
                                           << "(Already on this layer: " << layer << ")");
        return;
    }

    // Verify if the object is a child (if it is its layer must be its parents layer)
    if (o->hasParent)
    {
        Object *p = o->parent;
        if (!p || !p->IsRegistered())
        {
            LOG_ERR("Failed to set layer of: " << o->name << '-' << o
                                               << " (NULL pointer to parent or not registered parent)");
            return;
        }

        if (p->toBeMoved)
        {
            LOG_ERR("Failed to set layer of: " << o->name << '-' << o
                                               << " (Cannot be on a different layer than its parent: " << p->name << '-' << p
                                               << ") Moving with the parent on layer: " << p->newLayer);
        }
        else
        {
            LOG_ERR("Failed to set layer of: " << o->name << '-' << o
                                               << " (Cannot be on a different layer than its parent: " << p->name << '-' << p
                                               << ") Remaining on layer: " << p->layer);
        }

        return;
    }

    // Mark the object to be moved
    o->toBeMoved = true;
    this->objectsToMove.push_back(o);

    // Set the objects new layer to be added to
    o->newLayer = layer;

    LOG("Marked: " << o->name << '-' << o
                   << " to move from layer: " << o->layer
                   << " to: " << o->newLayer);
}

void Scene::MoveObjects()
{
    for (int i = 0; i < objectsToMove.size(); i++)
    {
        // Get the object to be moved and set the pointer tu null in the list
        Object *o = objectsToMove.at(i);
        objectsToMove[i] = nullptr;

        // Verify the object to exist
        if (!o || !o->IsRegistered())
        {
            LOG_ERR("Failed to move object (NULL pointer or not registered)");
            continue;
        }

        // Set the objects layer
        int ol = o->layer, l = o->newLayer;
        o->layer = l;
        o->newLayer = 0;
        o->toBeMoved = false;

        // Verify if the object is in the old layer
        size_t index = o->objectIndex;
        auto &layer = this->layers[ol];
        if (!(index < layer.size() && layer[index] == o))
        {
            LOG_ERR("Failed to move: " << o->name << '-' << o
                                       << " from: " << this->name << '-' << this
                                       << " layer: " << ol << " to layer: " << l
                                       << " (Not found in list)");
        }
        else
        {
            // Remove the object from the old layer
            layer.at(index) = layer.back();
            layer.at(index)->objectIndex = index;
            layer.pop_back();
        }

        // Add the object to the new layer
        this->layers[l].push_back(o);
        o->objectIndex = this->layers[l].size() - 1;

        LOG("Moved: " << o->name << '-' << o
                      << " from: " << this->name << '-' << this
                      << " layer: " << ol << " to layer: " << l);

        // Move all objects children and all of their children
        std::vector<Object *> allChildren = o->GetChildren();
        for (int j = 0; j < allChildren.size(); j++)
        {
            Object *c = allChildren.at(j);

            if (!c || !c->IsRegistered())
                continue;

            const std::vector<Object *> &children = c->GetChildren();
            allChildren.insert(allChildren.end(), children.begin(), children.end());

            c->layer = o->layer;
            LOG("Moved: " << c->name << '-' << c
                          << " from: " << this->name << '-' << this
                          << " layer: " << ol
                          << " to its new parent's layer: " << c->layer);
        }
        allChildren.clear();
    }

    objectsToMove.clear();
}

void Scene::OnEvent(sf::Event event)
{
    for (size_t i = 0; i < this->eventSubscribers[event.type].size(); i++)
    {
        Object *o = this->eventSubscribers.at(event.type).at(i);
        // Verify the object to exist
        if (!o || !o->IsRegistered())
        {
            LOG_ERR("Failed to call object OnEvent() (NULL pointer or not registered)");
            continue;
        }

        bool active = true;
        Object *p = o;
        while (p && p->IsRegistered() && active)
        {
            active = p->active;
            p = p->parent;
        }

        if (p && !p->IsRegistered())
        {
            LOG_ERR("Failed to call: " << o->name << '-' << o
                                       << " OnEvent() (NULL pointer to parent or not registered parent)");
            continue;
        }

        if (!active)
            continue;

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
                LOG_ERR("Failed to update object (NULL pointer)");
                continue;
            }

            if (!o->IsRegistered())
            {
                LOG_ERR("Failed to update: " << o->name << '-' << o
                                             << " (Not registered to the scene)");
                continue;
            }

            if (o->IsActive())
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
                LOG_ERR("Failed to draw object (NULL pointer)");
                continue;
            }

            if (!o->IsRegistered())
            {
                LOG_ERR("Failed to draw: " << o->name << '-' << o
                                           << " (Not registered to the scene)");
                continue;
            }

            if (o->IsVisible())
                o->Draw(window);
        }
}

void Scene::GetCollisions(Object *target, std::vector<Object *> &outCollisions)
{
    outCollisions.clear();

    if (!target || !target->IsRegistered())
    {
        LOG_ERR("Failed to get colliders with target (NULL pointer or not register)");
        return;
    }

    if (!target->IsCollider())
    {
        LOG_ERR("Failed to get colliders with: " << target->name << '-' << target
                                                 << " (Is not a collider)");
        return;
    }

    bool active = true;
    Object *p = target;
    while (p && p->IsRegistered() && active)
    {
        active = p->active;
        p = p->parent;
    }

    if (p && !p->IsRegistered())
    {
        LOG_ERR("Failed to get colliders with: " << target->name << '-' << target
                                                 << " (NULL pointer to parent or not registered parent)");
        return;
    }

    if (!active)
        return;

    sf::FloatRect targetBounds = target->GetBounds();
    for (Object *other : this->colliders)
    {
        if (!other || !other->IsRegistered())
        {
            LOG_ERR("Failed to check collision between: " << target->name << '-' << target
                                                          << " and other (NULL pointer or not register)");
            continue;
        }

        if (other == target)
            continue;

        active = true;
        Object *p = other;
        while (p && p->IsRegistered() && active)
        {
            active = p->active;
            p = p->parent;
        }

        if (p && !p->IsRegistered())
        {
            LOG_ERR("Failed to check collision between: " << target->name << '-' << target
                                                          << " and: " << other->name << '-' << other
                                                          << " (NULL pointer to parent or not registered parent)");
            continue;
        }

        if (!active)
            continue;

        if (targetBounds.intersects(other->GetBounds()))
            outCollisions.push_back(other);
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

    this->nextScene = nullptr;
    this->activeScene = nullptr;
    this->changingScene = false;
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
        LOG_ERR("Failed to set scene (NULL pointer)");
        return;
    }

    // Changes the scene
    Scene *previousScene = this->activeScene;
    this->activeScene = nextScene;

    // Sets the flag to stop the changing
    nextScene = nullptr;
    this->changingScene = false;

    LOG("Active scene is set to: "
        << activeScene->name << '-' << activeScene);

    // Deletes the previous scene if it exists
    if (previousScene)
        delete previousScene;
}

void SceneManager::AddObject(Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to add object to active scene (NULL pointer to scene)");
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
        LOG_ERR("Failed to remove object from active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->RemoveObject(o);
}

void SceneManager::SetObjectParent(Object *p, Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to set objects parent in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->SetObjectParent(p, o);
}

void SceneManager::SetObjectLayer(int layer, Object *o)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to set objects layer in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->SetObjectLayer(layer, o);
}

void SceneManager::DeleteObjects()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to delete marked objects in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->DeleteObjects();
}

void SceneManager::ChangeParents()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to move marked objects to parents in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->ChangeParents();
}

void SceneManager::MoveObjects()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to move marked objects to layers in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->MoveObjects();
}

void SceneManager::OnEvent(sf::Event event)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to react to events from active scene's objects (NULL pointer to scene)");
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
        LOG_ERR("Failed to update scene objects (NULL pointer to scene)");
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
        LOG_ERR("Failed to draw scene objects (NULL pointer to scene)");
        return;
    }

    // Update the view of the window
    window.setView(this->activeScene->camera);

    // Draws all the visible objects in the active scene
    this->activeScene->Draw(window);
}

void SceneManager::GetCollisions(Object *target, std::vector<Object *> &outCollisions)
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to set objects layer in active scene (NULL pointer to scene)");
        return;
    }

    this->activeScene->GetCollisions(target, outCollisions);
}

sf::View &SceneManager::GetCamera()
{
    // Verify the active scene to exist
    if (!this->activeScene)
    {
        LOG_ERR("Failed to get active scene camera (NULL pointer to scene)");
        return this->defaultCamera;
    }

    return this->activeScene->camera;
}
