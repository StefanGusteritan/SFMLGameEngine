#include "TestGame.hpp"

class TestObjChild : public Child, public CircleObject
{
private:
    float radius, speed;
public:
    TestObjChild(Parent *p) : Child(p), CircleObject()
    {
        this->circle.setRadius(radius);
        this->circle.setFillColor(sf::Color::Blue);
    }

    void Update() override
    {
        if(this->localPosition.x <= 880)
            this->localPosition += sf::Vector2f(0, 1) * speed * game.GetDeltaTime();

        this->Child::Update();
        this->CircleObject::Update();
    }
};

class TestObj : public CircleObject, public Parent
{
private:
    float radius = 100, speed = 50, time = 5, timer = 0;

public:
    TestObj() : CircleObject()
    {
        this->CircleObject::SetPosition(sf::Vector2f(s1State, 0));
        this->circle.setRadius(radius);
        this->circle.setFillColor(sf::Color::Cyan);
    }

    void Update() override
    {
        if (this->CircleObject::position.x < 1720)
            this->CircleObject::SetPosition(this->CircleObject::position + sf::Vector2f(1, 0) * speed * game.GetDeltaTime());

    /*
        if (timer < time)
            timer += game.GetDeltaTime();
        else
            game.SetActiveScene(new Scene2);
    */

        this->CircleObject::Update();
    }

    void Delete() override
    {
        s1State = this->CircleObject::position.x;
        this->Parent::Delete();
    }
};

class TestObjSquare : public RectangleObject
{
private:
    float sideLength = 200, speed = 20, time = 5, timer = 0;

public:
    TestObjSquare() : RectangleObject()
    {
        this->SetPosition(sf::Vector2f(0, s2State));
        this->rectangle.setSize(sf::Vector2f(sideLength, sideLength));
        this->rectangle.setFillColor(sf::Color::Magenta);
    }

    void Update() override
    {
        if (this->position.y < 880)
            this->SetPosition(this->position + sf::Vector2f(0, 1) * speed * game.GetDeltaTime());

        if (timer < time)
            timer += game.GetDeltaTime();
        else
            game.SetActiveScene(new Scene1);

        this->RectangleObject::Update();
    }

    void Delete() override
    {
        s2State = position.y;
        this->RectangleObject::Delete();
    }
};
