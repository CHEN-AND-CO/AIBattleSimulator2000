#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>

/*
                CONVENTION MAP

1: Herbe, Franchissable
2: Foret, Infranchissable, Ressource
3: Riviere, Infranchissable
*/

/*
                CONVENTION BUILDING

1: Town
2: Fort
*/

template <typename T>  // define a vector of vector
using dVector = typename std::vector<std::vector<T>>;

class Game {
 public:
  bool loadFile(const std::string& fileName);

  dVector<int> getMap() const { return mMap; }
  dVector<std::pair<sf::Color, int>> getBuildings() const {
    return mMapBuilding;
  }
  dVector<std::pair<sf::Color, int>> getEntities() const {
    return mMapEntities;
  }

 private:
  dVector<int> mMap;
  dVector<std::pair<sf::Color, int>> mMapBuilding;
  dVector<std::pair<sf::Color, int>> mMapEntities;
};

#endif