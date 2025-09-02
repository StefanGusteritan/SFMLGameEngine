#include "TestGame.hpp"

class Troop : public RectangleObject
{
private:
    float size = 200, speed = 25, targetOffset = 25, clickTime = 0.2f, clickTimer = 0;
    bool moving = false, selected = false, clickTimeout = false;
    sf::Vector2f target;

    float cameraSpeed = 20;

    void Select()
    {
        std::cout << "Troop: " << this << " selected\n";
        selected = true;
        this->rectangle.setFillColor(sf::Color::Blue);
    }

    void Deselect()
    {
        std::cout << "Troop: " << this << " deselected\n";
        selected = false;
        this->rectangle.setFillColor(sf::Color::White);
    }

public:
    Troop() : RectangleObject()
    {
        this->rectangle.setSize(sf::Vector2f(size, size));
        this->rectangle.setFillColor(sf::Color::White);
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
        game.GetSceneCamera()->move(cameraMoveDirection * cameraSpeed * game.GetDeltaTime());

        // Move the troop twords a target
        if (moving)
        {
            sf::Vector2f direction = target - (this->GetPosition() + sf::Vector2f(size / 2, size / 2));
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance >= targetOffset)
                this->Move(direction, speed * game.GetDeltaTime());
            else
            {
                moving = false;
                std::cout << "Troop: " << this << " reached target\n";
            }
        }

        // Time between mose clicks
        if (clickTimeout)
        {
            if (clickTimer < clickTime)
                clickTimer += game.GetDeltaTime();
            else
            {
                clickTimeout = false;
                clickTimer = 0;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !clickTimeout)
        {
            clickTimeout = true;

            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*game.GetWindow()));
            mousePosition += game.GetSceneCamera()->getCenter();
            mousePosition -= game.GetSceneCamera()->getSize() / 2.f;
            sf::Vector2f nvCorner = this->GetPosition(), seCorner = nvCorner + sf::Vector2f(size, size);

            // if the troop is clicked then it's selected/deselected
            if (mousePosition.x >= nvCorner.x && mousePosition.x <= seCorner.x && mousePosition.y >= nvCorner.y && mousePosition.y <= seCorner.y)
                selected ? Deselect() : Select();
            // if the click is anyware else the troop target will change
            else if (selected)
            {
                Deselect();
                moving = true;
                target = mousePosition;
                std::cout << "Troop: " << this << " target set to (" << target.x << ' ' << target.y << ')' << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            game.SetActiveScene(playerScene);

        this->RectangleObject::Update();
    }
};
