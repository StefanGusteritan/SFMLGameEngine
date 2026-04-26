#include "TestGame.h"

class TestChild : public RectangleObject
{
public:
    TestChild(Object *p) : RectangleObject("Child", 1, p)
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::Green);
        this->rectangle.setOrigin(size / 2, size / 2);
        this->SetPosition(sf::Vector2f(200, 100));
        this->SetRotation(45);
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return std::vector<sf::Event::EventType>{sf::Event::KeyPressed};
    }

private:
    float size = 100, speed = 20;

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::C)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    game.sceneManager.SetObjectLayer(3, this);
                else
                    game.sceneManager.RemoveObject(this);
            }
    }
};

class TestParent : public RectangleObject
{
public:
    TestParent() : RectangleObject(2)
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::Blue);
        this->rectangle.setOrigin(size / 2, size / 2);
        this->SetPosition(sf::Vector2f(960, 540));
        new TestChild(this);
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return std::vector<sf::Event::EventType>{sf::Event::KeyPressed};
    }

private:
    float size = 100, speed = 15;

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::P)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    game.sceneManager.SetObjectLayer(0, this);
                else
                    game.sceneManager.RemoveObject(this);
            }
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
        Move(moveDirection, speed, game.time.GetDT());

        float rotateDirection = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            rotateDirection += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            rotateDirection -= 1;
        this->Rotate(rotateDirection, speed, game.time.GetDT());

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

        this->RectangleObject::Update();
    }
};