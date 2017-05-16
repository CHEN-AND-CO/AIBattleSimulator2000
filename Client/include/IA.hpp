#ifndef IA_HPP
#define IA_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Game.hpp"

class IA {
 public:
  IA(Game *game, sf::Color color);
  
  void run();
  bool collect(int index);
  bool store(int index);
  
  int toForest(int index);
  int toHome(int index);

 private:
  Game* mGame;
  sf::Color mColor;
  
  std::vector<unsigned> action;
  std::vector<unsigned> state;
  std::vector<unsigned> count;
  
  sf::Clock clock;
  sf::Time delay;
};

#endif
