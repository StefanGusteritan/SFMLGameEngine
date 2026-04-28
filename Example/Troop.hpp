#include "TestGame.h"

class Troop : public RectangleObject
{
public:
    Troop() : RectangleObject("Troop")
    {
        this->SetSize({size, size});
        this->SetFillColor(sf::Color::White);
        this->SetOrigin({size / 2, size / 2});
    }

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return std::vector<sf::Event::EventType>{sf::Event::KeyPressed, sf::Event::MouseButtonPressed};
    }

private:
    float size = 200, speed = 25, targetOffset = 25;
    bool moving = false, selected = false;
    sf::Vector2f target;

    float cameraSpeed = 20;

    void Select()
    {
        LOG("Troop: " << this << " selected");
        selected = true;
        this->SetFillColor(sf::Color::Blue);
    }

    void Deselect()
    {
        LOG("Troop: " << this << " deselected");
        selected = false;
        this->SetFillColor(sf::Color::White);
    }

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::N)
                game.sceneManager.ChangeScene(playerScene);
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(game.GetWindow()));
                mousePosition += game.sceneManager.GetCamera().getCenter();
                mousePosition -= game.sceneManager.GetCamera().getSize() / 2.f;
                sf::Vector2f nvCorner = this->GetPosition() - sf::Vector2f(size / 2, size / 2),
                             seCorner = nvCorner + sf::Vector2f(size, size);

                // if the troop is clicked then it's selected/deselected
                if (mousePosition.x >= nvCorner.x && mousePosition.x <= seCorner.x && mousePosition.y >= nvCorner.y && mousePosition.y <= seCorner.y)
                    selected ? Deselect() : Select();
                // if the click is anyware else the troop target will change
                else if (selected)
                {
                    Deselect();
                    moving = true;
                    target = mousePosition;
                    LOG("Troop: " << this << " target set to (" << target.x << ' ' << target.y << ')');
                }
            }
        }
    }

    void Update() override
    {
        sf::Vector2f cameraMoveDirection = sf::Vector2f(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            cameraMoveDirection.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            cameraMoveDirection.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            cameraMoveDirection.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            cameraMoveDirection.x += 1;
        float magnitude = sqrt(pow(cameraMoveDirection.x, 2) + pow(cameraMoveDirection.y, 2));
        if (magnitude != 0)
            cameraMoveDirection /= magnitude;
        game.sceneManager.GetCamera().move(cameraMoveDirection * cameraSpeed * game.time.GetDT());

        // Move the troop twords a target
        if (moving)
        {
            sf::Vector2f direction = target - this->GetPosition();
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance >= targetOffset)
                this->Move(direction, speed, game.time.GetDT());
            else
            {
                moving = false;
                LOG("Troop: " << this << " reached target");
            }
        }

        this->RectangleObject::Update();
    }
};
