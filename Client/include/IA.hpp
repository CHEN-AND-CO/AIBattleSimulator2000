#ifndef IA_HPP
#define IA_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include "Game.hpp"

struct Tile{
  sf::Vector2f position;
  std::shared_ptr<Tile> parent;
  int strength;
};

class IA {
 public:
  IA(Game *game, sf::Color color);
  
  void run();
  void close();
  bool collect(int index);
  bool store(int index);
  void move(const sf::Vector2f pos, int index);
  
  int toForest(int index);
  int toHome(int index);
  bool goTo(const sf::Vector2f pos, int index);
  
  sf::Vector2f findFreeTree(const sf::Vector2f pos, int index);
  sf::Vector2f findTown(const sf::Vector2f pos, int index);
  sf::Vector2f findNextTile(const sf::Vector2f pos, int index);
  
  void computePoints(const sf::Vector2f pos, std::vector<sf::Vector2f>& aroundPoints);
  int manhattan(int x1, int y1, int x2, int y2);
  int manhattan(const sf::Vector2f pos1, const sf::Vector2f pos2);
  
  bool isFree(const sf::Vector2f pos);
  bool isTileFree(const sf::Vector2f pos);
  bool posInMap(const sf::Vector2f pos);
  bool pointExist(const sf::Vector2f pos, std::vector<sf::Vector2f> aroundMap);
  
  void pause(unsigned time);

 private:
  Game* mGame;
  sf::Color mColor;
  
  std::vector<unsigned> action;
  std::vector<unsigned> state;
  std::vector<unsigned> count;
  
  sf::Clock clock;
  sf::Time delay;
  std::vector<sf::Vector2f> mPosition;
};

#endif
