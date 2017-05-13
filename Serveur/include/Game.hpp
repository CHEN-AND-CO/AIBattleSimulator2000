#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Player.hpp"

/*
                CONVENTION MAP

1: Herbe, Franchissable
2: Foret, Infranchissable, Ressource
3: Riviere, Infranchissable
*/

class Game {
  template <typename T>  // define a vector of vector
  using dVector = typename std::vector<std::vector<T>>;

 public:
  bool loadFile(const std::string& fileName);

  dVector<int> getMap() const { return mMap; }
  std::vector<Building> getBuildings() const;
  std::vector<Entity> getEntities() const;

  void addEntity(const EntityType& entT, const sf::Color& col,
                 const sf::Vector2f& pos) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addEntity(entT, col, pos);
      }
    }
  }

  void addBuilding(const BuildingType& entT, const sf::Color& col,
                   const sf::Vector2f& pos) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addBuilding(entT, col, pos);
      }
    }
  }

  void clearMaps();

  bool isGameFinish() const;
  sf::Color getWinner() const;

 private:
  std::vector<std::vector<int>> mMap;
  std::vector<Player> mPlayer;
  // std::vector<sf::Color> t;
};

#endif
