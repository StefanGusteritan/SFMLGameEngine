#pragma once
#include "TestGame.h"

// A Gun that belongs to a Ship - Now a Rectangle to make rotation visible
class ShipGun : public RectangleObject
{
public:
    ShipGun(Object *parent, sf::Color color, sf::Vector2f offset)
        : RectangleObject("Gun", parent)
    {
        sf::Vector2f size(25.f, 8.f);
        this->rectangle.setSize(size);
        this->rectangle.setOrigin(0.f, size.y / 2.f); // Rotate around the base
        this->rectangle.setFillColor(color);
        this->SetPosition(offset);
    }

    void Update() override
    {
        // Spin the gun barrel locally - very visible now
        this->Rotate(200.f, game.time.GetDT());
        this->RectangleObject::Update();
    }
};

// A Complex Parent Object with Bouncing and Rotation
class ComplexShip : public RectangleObject
{
private:
    sf::Vector2f velocity;
    float rotationSpeed;

public:
    ComplexShip(sf::Vector2f pos, int startLayer, std::string name = "Ship")
        : RectangleObject(name, startLayer)
    {
        sf::Vector2f size(60.f, 40.f);
        this->rectangle.setSize(size);
        this->rectangle.setOrigin(size.x / 2.f, size.y / 2.f);
        this->rectangle.setFillColor(sf::Color::White);
        this->rectangle.setOutlineThickness(2.f);
        this->rectangle.setOutlineColor(sf::Color::Cyan);
        this->SetPosition(pos);

        // Random movement
        this->velocity = {(float)(rand() % 100 + 50), (float)(rand() % 100 + 50)};
        this->rotationSpeed = (float)(rand() % 40 + 20);

        // Add Children in Constructor
        new ShipGun(this, sf::Color::Red, {20.f, -15.f});
        new ShipGun(this, sf::Color::Red, {20.f, 15.f});
    }

    void Update() override
    {
        // 1. Screen Bouncing (1920x1080)
        sf::Vector2f pos = this->GetPosition();
        if (pos.x < 50 || pos.x > 1870)
            velocity.x *= -1;
        if (pos.y < 50 || pos.y > 1030)
            velocity.y *= -1;

        // 2. Continuous Rotation (makes guns orbit)
        this->Rotate(rotationSpeed, game.time.GetDT());

        // 3. Movement
        this->Move(velocity, game.time.GetDT());

        this->RectangleObject::Update();
    }
};

// A Space Station to test deep hierarchies
class SpaceStation : public CircleObject
{
public:
    SpaceStation(sf::Vector2f pos) : CircleObject("Station", 0)
    {
        float radius = 80.f;
        this->circle.setRadius(radius);
        this->circle.setOrigin(radius, radius);
        this->circle.setFillColor(sf::Color(50, 50, 50));
        this->circle.setOutlineThickness(5.f);
        this->circle.setOutlineColor(sf::Color::Yellow);
        this->SetPosition(pos);
    }
    void Update() override
    {
        this->Rotate(-10.f, game.time.GetDT());
        this->CircleObject::Update();
    }
};

// Controls the test via keyboard
class StressTestController : public Object
{
private:
    ComplexShip *ship1;
    ComplexShip *ship2;
    SpaceStation *station;

public:
    StressTestController(ComplexShip *s1, ComplexShip *s2)
        : Object("Controller"), ship1(s1), ship2(s2), station(nullptr) {}

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return {sf::Event::KeyPressed};
    }

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // [D] - DELETE SHIP 1
            if (event.key.code == sf::Keyboard::D)
            {
                if (ship1 && !ship1->IsMarkedToBeDeleted())
                {
                    std::cout << "\n--- [TEST] Deleting Ship 1 and its Guns ---" << std::endl;
                    game.sceneManager.RemoveObject(ship1);
                }
            }

            // [L] - CYCLE LAYER FOR SHIP 2
            if (event.key.code == sf::Keyboard::L)
            {
                if (ship2 && !ship2->IsMarkedToBeDeleted())
                {
                    int nextL = (ship2->GetLayer() == 5) ? 0 : 5;
                    std::cout << "\n--- [TEST] Ship 2 -> Layer " << nextL << " ---" << std::endl;
                    game.sceneManager.SetObjectLayer(nextL, ship2);
                }
            }

            // [S] - SPAWN STATION & REPARENT EVERYTHING
            if (event.key.code == sf::Keyboard::S)
            {
                if (!station)
                {
                    std::cout << "\n--- [TEST] Spawning Station & Capturing Ships ---" << std::endl;
                    station = new SpaceStation({960, 540});
                    game.sceneManager.AddObject(station);

                    if (ship1)
                        game.sceneManager.SetObjectParent(station, ship1);
                    if (ship2)
                        game.sceneManager.SetObjectParent(station, ship2);
                }
            }

            // [A] - RUNTIME ADDITION
            if (event.key.code == sf::Keyboard::A)
            {
                std::cout << "\n--- [TEST] Adding Random Ship ---" << std::endl;
                game.sceneManager.AddObject(new ComplexShip({(float)(rand() % 1000), (float)(rand() % 1000)}, 1));
            }

            // [K] - KAMIKAZE (Delete parent, but try to reparent child in same frame)
            if (event.key.code == sf::Keyboard::K)
            {
                if (ship2 && !ship2->GetChildren().empty())
                {
                    std::cout << "\n--- [CRITICAL TEST] Delete Parent, Reparent Child Simultaneously ---" << std::endl;
                    Object *gun = ship2->GetChildren().front();
                    game.sceneManager.RemoveObject(ship2);           // Mark parent for death
                    game.sceneManager.SetObjectParent(nullptr, gun); // Try to "save" the gun
                }
            }
        }
    }
};
