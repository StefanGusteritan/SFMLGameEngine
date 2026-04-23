#include "TestGame.h"
#include "Player.hpp"
#include "Troop.hpp"
#include "ParentChild.hpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

SceneBuilder playerScene("Player_Scene",
                         sf::Vector2f(1920, 1080),
                         sf::Vector2f(960, 540),
                         []()
                         {
                           return std::vector<Object *>{new Player};
                         });

SceneBuilder troopScene("Troop_Scene",
                        sf::Vector2f(1920, 1080),
                        sf::Vector2f(960, 540),
                        []()
                        {
                          return std::vector<Object *>{new Troop};
                        });

SceneBuilder parentChildScene("Parent-Child_Scene",
                              sf::Vector2f(1920, 1080),
                              sf::Vector2f(960, 540),
                              []()
                              {
                                std::vector<Object *> obj;
                                TestParent *p = new TestParent;
                                obj.push_back(p);
                                obj.push_back(new TestChild(p));
                                return obj;
                              });
