#include "TestGame.h"
#include "Player.hpp"
#include "Troop.hpp"
#include "ParentChild.hpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

SceneBuilder playerScene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540), [](Scene *s)
                         { s->AddObject(new Player); });

SceneBuilder troopScene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540), [](Scene *s)
                        { s->AddObject(new Troop); });

SceneBuilder parentChildScene(sf::Vector2f(1920, 1080), sf::Vector2f(960, 540), [](Scene *s)
                              { TestParent *p = new TestParent;
                                s->AddObject(p);
                                s->AddObject(new TestChild(p)); });
