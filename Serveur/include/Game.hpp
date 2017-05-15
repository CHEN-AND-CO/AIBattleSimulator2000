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
 public:
  bool loadFile(const std::string& fileName);

  std::vector<std::vector<int>> getMap() const { return mMap; }
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

  void addBuilding(const BuildingType& buildT, const sf::Color& col,
                   const sf::Vector2f& pos) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addBuilding(buildT, col, pos);
      }
    }
  }

  void addPlayer(const sf::Color& col, const sf::Vector2f pos) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        return;
      }
    }
    mPlayer.push_back(Player(col, pos));
  }

  void moveEntity(Direction dir, const sf::Color& col, int i);

  void clearPlayer() {
    for (auto& play : mPlayer) {
      play.clearMaps();
    }
  }

  bool isGameFinish() const;
  sf::Color getWinner() const;

 private:
  std::vector<std::vector<int>> mMap;
  std::vector<Player> mPlayer;
};

#endif
