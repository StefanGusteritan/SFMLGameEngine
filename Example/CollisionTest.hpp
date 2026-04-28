#pragma once
#include "TestGame.h"

// A simple player that moves and checks for collisions
class TestPlayer : public RectangleObject
{
private:
    // Basic movement
    float speed = 200.f;
    Collider *myCollider;
    std::vector<Object *> currentCollisions;

public:
    TestPlayer() : RectangleObject("Player")
    {
        SetSize({50.f, 50.f});
        SetFillColor(sf::Color::Blue);
        SetPosition({400.f, 300.f});
        SetOrigin({25.f, 25.f});

        // Add a collider as a child
        myCollider = new Collider("PlayerCollider", this);
        myCollider->SetSize({50.f, 50.f});
        myCollider->SetOrigin({25.f, 25.f});
        // We can show it for debugging
        Collider::ToggleDebug(true);
    }

    // Return the collider so it can be registered by the scene
    const std::vector<Object *> GetChildrenToAdd() override
    {
        return {myCollider};
    }

    void Update() override
    {
        this->RectangleObject::Update();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            Move({0, -1}, speed, game.time.GetDT());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            Move({0, 1}, speed, game.time.GetDT());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Move({-1, 0}, speed, game.time.GetDT());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Move({1, 0}, speed, game.time.GetDT());

        // Check for collisions using the global game reference
        this->CheckCollision();
    }

    // We'll use a custom method to check collisions, or do it in the Scene/Game loop
    void CheckCollision()
    {
        game.sceneManager.GetCollisions(myCollider, currentCollisions);
        if (!currentCollisions.empty())
        {
            LOG("Player is colliding with " << currentCollisions.size() << " objects!");
            SetFillColor(sf::Color::Red); // Visual feedback
        }
        else
        {
            SetFillColor(sf::Color::Blue);
        }
    }
};

// A static wall
class TestWall : public RectangleObject
{
private:
    Collider *wallCollider;

public:
    TestWall(sf::Vector2f pos, sf::Vector2f size) : RectangleObject("Wall")
    {
        SetSize(size);
        SetPosition(pos);
        SetFillColor(sf::Color::Green);

        wallCollider = new Collider("WallCollider", this);
        wallCollider->SetSize(size);
        wallCollider->SetOrigin(size / 2.f);
        SetOrigin(size / 2.f);
    }

    const std::vector<Object *> GetChildrenToAdd() override
    {
        return {wallCollider};
    }
};
