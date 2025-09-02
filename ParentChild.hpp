#include "TestGame.hpp"

class TestChild : public CircleObject, public Child
{
private:
    float size = 100, speed = 20;

public:
    TestChild(Parent *p) : CircleObject(), Child(p)
    {
        this->circle.setRadius(size / 2);
        this->circle.setFillColor(sf::Color::Green);
    }

    void Update() override
    {
        this->LocalMove(sf::Vector2f(1, 0), speed * game.GetDeltaTime());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            game.RemoveObject(this);

        this->Child::Update();
        this->CircleObject::Update();
    }
};

class TestParent : public RectangleObject, public Parent
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
        this->Parent::Update();
    }

    void Draw(sf::RenderWindow *window) override
    {
        this->RectangleObject::Draw(window);
        this->Parent::Draw(window);
    }
};