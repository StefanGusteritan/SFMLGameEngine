#include "TestGame.h"
#include "Player.hpp"
#include "Troop.hpp"
#include "ParentChild.hpp"
#include "StressTest.hpp"

Game game(sf::VideoMode(1920, 1080), "Test", sf::Style::Default);

SceneBuilder playerScene("Player_Scene",
                         sf::Vector2f(1920, 1080),
                         sf::Vector2f(960, 540),
                         []()
                         {
                           return std::vector<Object *>{new Player(1), new Player(0)};
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

SceneBuilder stressTestScene("Stress_Test",
                             sf::Vector2f(1920, 1080),
                             sf::Vector2f(960, 540),
                             []()
                             {
                               std::vector<Object *> obj;
                               ComplexShip *s1 = new ComplexShip({400, 300}, 0, "Ship1");
                               ComplexShip *s2 = new ComplexShip({400, 700}, 5, "Ship2");
                               obj.push_back(s1);
                               obj.push_back(s2);
                               obj.push_back(new StressTestController(s1, s2));
                               return obj;
                             });