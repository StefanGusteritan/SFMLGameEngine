#include "TestGame.h"
#include "Player.hpp"
#include "Troop.hpp"
#include "ParentChild.hpp"
#include "StressTest.hpp"
#include "CollisionTest.hpp"

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
                               obj.push_back(new StressTestController());
                               return obj;
                             });

SceneBuilder collisionTestScene("CollisionTest",
                                {800.f, 600.f}, // Camera Size
                                {400.f, 300.f}, // Camera Center
                                []()
                                {
                                  std::vector<Object *> objects;

                                  // Add Player
                                  objects.push_back(new TestPlayer());

                                  // Add some walls
                                  objects.push_back(new TestWall({200.f, 200.f}, {100.f, 50.f}, true));
                                  objects.push_back(new TestWall({600.f, 400.f}, {50.f, 150.f}, false));

                                  return objects;
                                });
