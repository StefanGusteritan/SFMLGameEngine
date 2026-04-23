#include "TestGame.h"

class Player : public RectangleObject
{
public:
    Player(int layer) : RectangleObject("Player", layer)
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        if (layer == 2)
            this->rectangle.setFillColor(sf::Color::Green);
        if (layer == 1)
            this->rectangle.setFillColor(sf::Color::Blue);
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        if (this->GetLayer() == 1)
            return std::vector<sf::Event::EventType>{sf::Event::KeyPressed};
        else
            return std::vector<sf::Event::EventType>();
    }

private:
    float size = 100, speed = 75;

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
        if (this->GetLayer() == 2)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                moveDirection.x += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                moveDirection.x -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                moveDirection.y += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                moveDirection.y -= 1;
        }
        else if (this->GetLayer() == 1)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                moveDirection.x += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                moveDirection.x -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                moveDirection.y += 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                moveDirection.y -= 1;
        }
        Move(moveDirection, speed * game.time.GetDT());

        this->RectangleObject::Update();
    }
};
