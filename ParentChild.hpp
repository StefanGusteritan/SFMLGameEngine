#include "TestGame.h"

class TestChild : public RectangleObject
{
private:
    float size = 100, speed = 20;

public:
    TestChild(Object *p) : RectangleObject(p)
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::Green);
        this->rectangle.setOrigin(size / 2, size / 2);
        this->SetPosition(sf::Vector2f(200, 100));
        this->SetRotation(45);
    }

    void Update() override
    {
        // this->Move(sf::Vector2f(1, 0), speed * game.time.GetDT());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            game.sceneManager.RemoveObject(this);

        this->RectangleObject::Update();
    }
};

class TestParent : public RectangleObject
{
private:
    float size = 100, speed = 15;

public:
    TestParent() : RectangleObject()
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::Blue);
        this->rectangle.setOrigin(size / 2, size / 2);
        this->SetPosition(sf::Vector2f(960, 540));
    }

    void Update() override
    {
        // this->Move(sf::Vector2f(0, 1), speed * game.time.GetDT());

        sf::Vector2f moveDirection = sf::Vector2f(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            moveDirection.x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            moveDirection.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            moveDirection.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            moveDirection.y -= 1;
        Move(moveDirection, speed * game.time.GetDT());

        float rotateDirection = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            rotateDirection += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            rotateDirection -= 1;
        this->Rotate(rotateDirection, speed * game.time.GetDT());

        sf::Vector2f scaleDirection = sf::Vector2f(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            scaleDirection.x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            scaleDirection.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            scaleDirection.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            scaleDirection.y -= 1;
        this->SetScale(this->GetScale() + scaleDirection * 2.f * game.time.GetDT());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            game.sceneManager.RemoveObject(this);

        this->RectangleObject::Update();
    }
};