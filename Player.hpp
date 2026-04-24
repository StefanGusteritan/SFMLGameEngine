#include "TestGame.h"

class Player : public RectangleObject
{
public:
    Player(int layer) : RectangleObject("Player", layer)
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        if (layer == 1)
            this->rectangle.setFillColor(sf::Color::Green);
        else
            this->rectangle.setFillColor(sf::Color::Blue);
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return std::vector<sf::Event::EventType>{sf::Event::KeyPressed};
    }

private:
    float size = 100, speed = 75;

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::N && this->GetLayer() == 1)
                game.sceneManager.ChangeScene(troopScene);
            if (event.key.code == sf::Keyboard::L)
            {
                if (this->GetLayer() == 0)
                    game.sceneManager.SetObjectLayer(2, this);
                else if (this->GetLayer() == 2)
                    game.sceneManager.SetObjectLayer(0, this);
            }
        }
    }

    void Update() override
    {
        sf::Vector2f moveDirection = sf::Vector2f(0, 0);
        if (this->GetLayer() == 1)
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
        else
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
