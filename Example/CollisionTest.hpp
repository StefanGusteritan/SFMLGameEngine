#pragma once
#include "TestGame.h"

// A simple player that moves and checks for collisions
class TestPlayer : public RectangleObject
{
private:
    // Basic movement
    sf::Vector2f movement;
    float speed = 200.f, dt, magnitude;
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
        myCollider->SetSize({48.f, 48.f});
        myCollider->SetOrigin({24.f, 24.f});
        // We can show it for debugging
        Collider::ToggleDebug(false);
    }

    // Return the collider so it can be registered by the scene
    const std::vector<Object *> GetChildrenToAdd() override
    {
        return {myCollider};
    }

    void Update() override
    {
        movement = sf::Vector2f();
        dt = game.time.GetDT();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += 1;

        magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);
        if (magnitude != 0)
            movement /= magnitude;

        if (movement.x != 0)
        {
            game.sceneManager.GetCollisions(
                myCollider->GetBoundsOffsetPosition({movement.x * speed * dt, 0}),
                myCollider,
                currentCollisions,
                true);
            if (!currentCollisions.empty())
                movement.x = 0;
        }
        if (movement.y != 0)
        {
            game.sceneManager.GetCollisions(
                myCollider->GetBoundsOffsetPosition({0, movement.y * speed * dt}),
                myCollider,
                currentCollisions,
                true);
            if (!currentCollisions.empty())
                movement.y = 0;
        }

        Move(movement, speed, dt);

        // Check for collisions using the global game reference
        this->CheckCollision();

        this->RectangleObject::Update();
    }

    // We'll use a custom method to check collisions, or do it in the Scene/Game loop
    void CheckCollision()
    {
        game.sceneManager.GetCollisions(myCollider, currentCollisions);
        if (!currentCollisions.empty())
        {
            if (GetFillColor() == sf::Color::Blue)
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
    TestWall(sf::Vector2f pos, sf::Vector2f size, bool solid) : RectangleObject("Wall")
    {
        SetSize(size);
        SetOrigin(size / 2.f);
        SetPosition(pos);

        if (solid)
            SetFillColor(sf::Color::Green);
        else
            SetFillColor(sf::Color{0, 255, 0, 63});

        wallCollider = new Collider("WallCollider", this);
        wallCollider->SetSolid(solid);
        wallCollider->SetSize({size.x - 2, size.y - 2});
        wallCollider->SetOrigin({(size.x - 2) / 2.f, (size.y - 2) / 2.f});
    }

    const std::vector<Object *> GetChildrenToAdd() override
    {
        return {wallCollider};
    }
};
