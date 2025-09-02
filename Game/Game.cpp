#include "Game.h"

Game::Game(sf::VideoMode windowSize, const char *windowTitle, sf::Uint32 windowStyle)
{
    this->changingScene = false;

    this->mainWindow.create(windowSize, windowTitle, windowStyle);
    std::cout << "Game window created with title: " << windowTitle << std::endl;
}

Game::~Game()
{
    delete this->nextScene;
    delete this->activeScene;
    DeleteObjects();
    std::cout << "Game destroyed." << std::endl;
}

sf::WindowBase *Game::GetWindow()
{
    return &this->mainWindow;
}

sf::View *Game::GetSceneCamera()
{
    return &this->activeScene->camera;
}

void Game::UpdateDeltaTime()
{
    this->deltaTime = this->dtClock.getElapsedTime().asSeconds();
    dtClock.restart();
}

float Game::GetDeltaTime()
{
    return this->deltaTime;
}

void Game::UpdateEvents()
{
    while (this->mainWindow.pollEvent(this->event))
    {
        // Close event
        if (this->event.type == sf::Event::Closed)
        {
            this->mainWindow.close();
        }
    }
}

void Game::SetActiveScene(SceneBuilder s)
{
    // Creates the scene
    this->nextScene = new Scene(s.GetCameraSize(), s.GetCameraCenter());
    // Creates and adds the objects to the scene
    s.addObjectsToScene(this->nextScene);

    // Sets the flag to change the scene when the Update() and Run() methods are over
    this->changingScene = true;
}

void Game::ChangeScene()
{
    // Verify the next scene to exist
    if (!nextScene)
    {
        std::cout << "Failed to set scene (Null pointer)" << std::endl;
        return;
    }

    // Changes the scene
    Scene *previousScene = this->activeScene;
    this->activeScene = nextScene;
    nextScene = nullptr;

    // Sets the flag to stop the changing
    this->changingScene = false;
    std::cout << "Active scene is set to " << activeScene << std::endl;

    // Deletes the previous scene
    if (!previousScene)
        std::cout << "Failed to delete previous scene (Null pointer)" << std::endl;
    else
    {
        std::list<Object *> sceneObjects = previousScene->GetObjects();
        for (Object *o : sceneObjects)
            this->RemoveObject(o);
        delete previousScene;
    }
}

void Game::AddObject(Object *o)
{
    // Verify object to exist
    if (!o)
    {
        std::cout << "Failed to add object (Null pointer)" << std::endl;
        return;
    }

    // Add to the active scene
    this->activeScene->AddObject(o);
}

void Game::RemoveObject(Object *o)
{
    // Verify the object to exist
    if (!o)
    {
        std::cout << "Failed to remove object (Null pointer)" << std::endl;
        return;
    }

    // Add object to the list to be deleted
    objectsToDelete.push_back(o);

    // If the object is a parent remove its children and add them to the list to be deleted
    Parent *p = dynamic_cast<Parent *>(o);
    if (p)
    {
        std::list<Object *> children = p->GetChildren();
        for (Object *obj : children)
            this->RemoveObject(obj);
    }
}

void Game::DeleteObjects()
{
    while (!this->objectsToDelete.empty())
    {
        Object *o = objectsToDelete.back();

        // Verify object to exist
        if (!o)
            std::cout << "Failed to remove object (Null pointer)";

        else
        {
            // If the object is a child, it's removed from its parent
            Child *c = dynamic_cast<Child *>(o);
            if (c)
                c->GetParent()->RemoveChild(c);
            // If the object is not a child, it's removed from the active scene
            else
                this->activeScene->RemoveObject(o);

            objectsToDelete.remove(o);
            delete o;
        }
    }
}

void Game::Update()
{
    // Get the new deltaTime
    this->UpdateDeltaTime();

    // Update the events
    this->UpdateEvents();

    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to update scene objects (Null pointer to scene)" << std::endl;
        return;
    }
    // Update all active objects in the active scene
    this->activeScene->Update();

    // Update the view of the window
    this->mainWindow.setView(this->activeScene->camera);
}

void Game::Draw()
{
    // Clears the last frame
    this->mainWindow.clear();

    // Verify the active scene to exist
    if (!this->activeScene)
    {
        std::cout << "Failed to draw scene objects (Null pointer to scene)" << std::endl;
        return;
    }
    // Draws all the visible objects in the active scene
    this->activeScene->Draw(&this->mainWindow);

    this->mainWindow.display();
}

void Game::Run()
{
    while (this->mainWindow.isOpen())
    {
        if (changingScene)
            this->ChangeScene();
        this->DeleteObjects();

        this->Update();
        this->Draw();
    }
}