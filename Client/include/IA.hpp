#ifndef IA_HPP
#define IA_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Game.hpp"

struct Tile{
  sf::Vector2f position;
  std::shared_ptr<Tile> parent;
  int strength;
};

class IA {
 public:
  IA(Game *game, sf::RenderWindow *window, sf::Color color);
  
  void run();
  void close();
  bool collect(int index);
  bool store(int index);
  
  int toForest(int index);
  int toHome(int index);
  
  sf::Vector2f findFreeTree(const sf::Vector2f pos, int index);
  bool goTo(const sf::Vector2f pos, int index);
  
  bool posInMap(const sf::Vector2f pos);
  bool pointExist(const sf::Vector2f pos, std::vector<sf::Vector2f> aroundMap);
  void computePoints(const sf::Vector2f pos, std::vector<sf::Vector2f>& aroundPoints);
  bool isFree(const sf::Vector2f pos);
  bool isTreeFree(const sf::Vector2f pos);
  
  void pause(unsigned time);

 private:
  Game* mGame;
  sf::RenderWindow* mWindow;
  sf::Color mColor;
  
  std::vector<unsigned> action;
  std::vector<unsigned> state;
  std::vector<unsigned> count;
  
  sf::Clock clock;
  sf::Time delay;
  std::vector<sf::Vector2f> mPosition;
};

#endif
