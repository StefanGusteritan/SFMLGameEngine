#pragma once
#include <SFML/System.hpp>

class TimeManager
{
private:
    // Delta Time - The time it takes to update and render a frame
    sf::Clock dtClock;
    float deltaTime;

    // Update the deltaTime by getting the elapsed time since the last update and restart the clock
    void UpdateDeltaTime();

    friend class Game;

public:
    // Get the deltaTime
    float GetDT();
};
