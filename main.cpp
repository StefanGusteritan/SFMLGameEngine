#include "Game\Game.cpp"
#include "Game\Scene.cpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

float s1State = 0, s2State = 0;

class Scene1 : public Scene
{
public:
    Scene1();
};

class Scene2 : public Scene
{
public:
    Scene2();
};

class TestObj : public CircleObject
{
private:
    float radius = 100, speed = 50, time = 5, timer = 0;

public:
    TestObj() : CircleObject()
    {
        this->SetPosition(sf::Vector2f(s1State, 0));
        this->circle.setRadius(radius);
        this->circle.setFillColor(sf::Color::Cyan);
    }

    void Update() override
    {
        if (this->position.x < 1720)
            this->SetPosition(this->position + sf::Vector2f(1, 0) * speed * game.GetDeltaTime());

        if (timer < time)
            timer += game.GetDeltaTime();
        else
            game.SetActiveScene(new Scene2);

        this->CircleObject::Update();
    }

    void Delete() override
    {
        s1State = this->position.x;
        this->CircleObject::Delete();
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

Scene1::Scene1()
{
    this->AddObject(new TestObj);
}

Scene2::Scene2()
{
    this->AddObject(new TestObjSquare);
}

int main()
{
    game.SetActiveScene(new Scene1);

    game.Run();

    return 0;
}