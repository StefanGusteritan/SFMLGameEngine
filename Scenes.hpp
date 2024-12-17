#include "TestGame.hpp"
#include "TestObj.hpp"

Scene1::Scene1()
{
    this->AddObject(new TestObj);
}

Scene2::Scene2()
{
    this->AddObject(new TestObjSquare);
}