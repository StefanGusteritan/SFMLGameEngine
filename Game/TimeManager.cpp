#include "TimeManager.h"

void TimeManager::UpdateDeltaTime()
{
    this->deltaTime = this->dtClock.getElapsedTime().asSeconds();
    dtClock.restart();
}

float TimeManager::GetDT()
{
    return this->deltaTime;
}
