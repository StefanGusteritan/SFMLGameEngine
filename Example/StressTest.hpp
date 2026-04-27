#pragma once
#include "TestGame.h"
#include <iomanip>
#include <sstream>

// A performance counter to see the impact of our optimizations
class FPSCounter : public TextObject
{
private:
    float timer = 0;
    int frames = 0;
    static sf::Font font;
    bool fontLoaded = false;

public:
    FPSCounter() : TextObject("FPS_Counter", 10)
    {
        // Try to load a system font (standard on most Linux/WSL distros)
        if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
        {
            this->text.setFont(font);
            this->text.setCharacterSize(24);
            this->text.setFillColor(sf::Color::Yellow);
            this->text.setOutlineColor(sf::Color::Black);
            this->text.setOutlineThickness(2);
            this->SetPosition({20, 20});
        }
        else if (font.loadFromFile("D:/Code/Compiler-Libraries/UbuntuMono[wght].ttf"))
        {
            this->text.setFont(font);
            this->text.setCharacterSize(24);
            this->text.setFillColor(sf::Color::Yellow);
            this->text.setOutlineColor(sf::Color::Black);
            this->text.setOutlineThickness(2);
            this->SetPosition({20, 20});
        }
    }

    void Update() override
    {
        timer += game.time.GetDT();
        frames++;

        if (timer >= 1.0f)
        {
            std::stringstream ss;
            ss << "FPS: " << frames << " | DT: " << std::fixed << std::setprecision(4) << game.time.GetDT();
            this->text.setString(ss.str());
            timer = 0;
            frames = 0;
        }
        this->TextObject::Update();
    }
};
sf::Font FPSCounter::font;

// A Gun that belongs to a Ship - Visible rotation test
class ShipGun : public RectangleObject
{
public:
    ShipGun(Object *parent, sf::Color color, sf::Vector2f offset)
        : RectangleObject("Gun", parent)
    {
        sf::Vector2f size(25.f, 8.f);
        this->rectangle.setSize(size);
        this->rectangle.setOrigin(0.f, size.y / 2.f);
        this->rectangle.setFillColor(color);
        this->SetPosition(offset);
    }

    void Update() override
    {
        // Spin guns locally
        this->Rotate(300.f, 1, game.time.GetDT());
        this->RectangleObject::Update();
    }
};

// A Complex Parent Object using the new GetChildrenToAdd pattern
class ComplexShip : public RectangleObject
{
private:
    sf::Vector2f velocity;
    float rotationSpeed;

public:
    ComplexShip(sf::Vector2f pos, int startLayer, std::string name = "Ship")
        : RectangleObject(name, startLayer)
    {
        sf::Vector2f size(40.f, 30.f);
        this->rectangle.setSize(size);
        this->rectangle.setOrigin(size.x / 2.f, size.y / 2.f);
        this->rectangle.setFillColor(sf::Color(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100));
        this->SetPosition(pos);

        this->velocity = {(float)(rand() % 200 - 100), (float)(rand() % 200 - 100)};
        this->rotationSpeed = (float)(rand() % 100 - 50);
    }

    // New pattern: Children are registered automatically after the parent
    const std::vector<Object *> GetChildrenToAdd() override
    {
        return std::vector<Object *>{
            new ShipGun(this, sf::Color::Red, {15.f, -10.f}),
            new ShipGun(this, sf::Color::Red, {15.f, 10.f})};
    }

    void Update() override
    {
        sf::Vector2f pos = this->GetPosition();
        if (pos.x < 20 || pos.x > 1900)
            velocity.x *= -1;
        if (pos.y < 20 || pos.y > 1060)
            velocity.y *= -1;

        this->Rotate(rotationSpeed, 1, game.time.GetDT());
        this->Move(velocity, 1, game.time.GetDT());

        this->RectangleObject::Update();
    }
};

// Mass-spawning controller to test O(1) list management and deferred ops
class StressTestController : public Object
{
private:
    bool chaosMode = false;
    std::vector<ComplexShip *> ships;

public:
    StressTestController() : Object("StressController") {}

    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override
    {
        return {sf::Event::KeyPressed};
    }

    const std::vector<Object *> GetChildrenToAdd() override
    {
        return {new FPSCounter()};
    }

    void OnEvent(sf::Event event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // [H] - HEAVY LOAD: Spawn 100 Ships (300 objects total)
            if (event.key.code == sf::Keyboard::H)
            {
                LOG("[STRESS] Spawning 100 Ships (300 entities)...");
                for (int i = 0; i < 100; ++i)
                {
                    ComplexShip *s = new ComplexShip({(float)(rand() % 1920), (float)(rand() % 1080)}, rand() % 5);
                    game.sceneManager.AddObject(s);
                    ships.push_back(s);
                }
            }

            // [L] - LAYER CHAOS: Move all ships to random layers simultaneously
            if (event.key.code == sf::Keyboard::L)
            {
                LOG("[STRESS] Moving all objects to random layers...");
                for (auto s : ships)
                {
                    if (s->IsRegistered())
                        game.sceneManager.SetObjectLayer(rand() % 10, s);
                }
            }

            // [C] - CLEAR: Remove everything
            if (event.key.code == sf::Keyboard::C)
            {
                LOG("[STRESS] Removing all registered ships...");
                for (auto s : ships)
                {
                    if (s->IsRegistered())
                        game.sceneManager.RemoveObject(s);
                }
                ships.clear();
            }

            // [X] - TOGGLE CHAOS MODE (Random per-frame stress)
            if (event.key.code == sf::Keyboard::X)
            {
                chaosMode = !chaosMode;
                LOG("[STRESS] Chaos Mode: " << (chaosMode ? "ON" : "OFF"));
            }
        }
    }

    void Update() override
    {
        if (chaosMode && ships.size() >= 5)
        {
            // Randomly move or delete ships every frame to test list stability
            for (int i = 0; i < 5; ++i)
            {

                int idx = rand() % ships.size();
                if (ships[idx]->IsRegistered())
                {
                    if (rand() % 100 < 5)
                    { // 5% chance to delete
                        game.sceneManager.RemoveObject(ships[idx]);
                        ships[idx] = ships.back();
                        ships.pop_back();
                    }
                    else // 95% chance to switch layer
                        game.sceneManager.SetObjectLayer(rand() % 10, ships[idx]);
                }
            }
        }
        this->Object::Update();
    }
};
