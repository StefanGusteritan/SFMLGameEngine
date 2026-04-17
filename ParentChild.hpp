#include "TestGame.h"

class TestChild : public CircleObject
{
private:
    float size = 100, speed = 20;

public:
    TestChild(Object *p) : CircleObject(p)
    {
        this->circle.setRadius(size / 2);
        this->circle.setFillColor(sf::Color::Green);
    }

    void Update() override
    {
        this->Move(sf::Vector2f(1, 0), speed * game.GetDeltaTime());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            game.RemoveObject(this);

        this->CircleObject::Update();
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
    }

    void Update() override
    {
        this->Move(sf::Vector2f(0, 1), speed * game.GetDeltaTime());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            game.RemoveObject(this);

        this->RectangleObject::Update();
    }
};