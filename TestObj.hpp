#include "TestGame.hpp"

class TestObjChild : public CircleObject, public Child
{
private:
    float radius = 100, speed = 25;

public:
    TestObjChild(Parent *p) : CircleObject(), Child(p)
    {
        this->circle.setRadius(radius);
        this->circle.setFillColor(sf::Color::Blue);
    }

    void Update() override
    {
        if (this->GetLocalPosition().y <= 880)
            this->LocalMove(sf::Vector2f(0, 1), speed * game.GetDeltaTime());

        std::cout << this->GetPosition().x << ' ' << this->GetPosition().y << '\r';

        this->Child::Update();
        this->CircleObject::Update();
    }
};

class TestObj : public CircleObject, public Parent
{
private:
    float radius = 100, speed = 50, time = 5, timer = 0;
    bool child = false;

public:
    TestObj() : CircleObject()
    {
        // this->SetPosition(sf::Vector2f(s1State, 0));
        this->circle.setRadius(radius);
        this->circle.setFillColor(sf::Color::Cyan);
    }

    void Update() override
    {
        if (!child)
        {
            child = true;
            game.GetActiveScene()->AddObject(new TestObjChild(this));
        }

        if (this->GetPosition().x < 1720)
            this->Move(sf::Vector2f(1, 0), speed * game.GetDeltaTime());

        if (timer < time)
            timer += game.GetDeltaTime();
        else
        {
            // game.SetActiveScene(new Scene2);
            this->SetVisible(!this->IsVisible());
            timer = 0;
        }

        this->CircleObject::Update();
    }
    /*
        void Delete() override
        {
            s1State = this->GetPosition().x;
            this->Parent::Delete();
        }
    */
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
        if (this->GetPosition().y < 880)
            this->Move(sf::Vector2f(0, 1), speed * game.GetDeltaTime());

        if (timer < time)
            timer += game.GetDeltaTime();
        else
            game.SetActiveScene(new Scene1);

        this->RectangleObject::Update();
    }

    void Delete() override
    {
        s2State = GetPosition().y;
        this->RectangleObject::Delete();
    }
};
