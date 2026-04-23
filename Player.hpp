#include "TestGame.h"

class Player : public RectangleObject
{
private:
    float size = 100, speed = 75;

public:
    Player() : RectangleObject("Player")
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::Green);
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return std::vector<sf::Event::EventType>{sf::Event::KeyPressed};
    }

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::N)
                game.sceneManager.ChangeScene(troopScene);
        }
    }

    void Update() override
    {

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

        this->RectangleObject::Update();
    }
};
