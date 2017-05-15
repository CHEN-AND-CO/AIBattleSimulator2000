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
  std::vector<Player> getPlayer() const { return mPlayer; }
  std::vector<Building> getBuildings() const;
  std::vector<Entity> getEntities() const;

  Player getPlayer(const sf::Color&) const;
  std::vector<Building> getBuildings(const sf::Color&) const;
  std::vector<Entity> getEntities(const sf::Color&) const;

  void addEntity(const EntityType& entT, const sf::Color& col, int index) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addEntity(entT, index);
        return;
      }
    }
  }

  void addBuilding(const BuildingType& buildT, const sf::Color& col,
                   int index) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addBuilding(buildT, index);
        return;
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

  bool moveEntity(const Direction& dir, const sf::Color& col, int i);
  bool collectRessource(const Direction& dir, const sf::Color& col, int index) {
    for (auto& p : mPlayer) {
      if (p.getColor() == col) {
        return p.collectRessource(*this, dir, index);
      }
    }
    return false;
  }
  bool putRessourcesInTown(const Direction& dir, const sf::Color& col,
                           int index);

  void clearPlayer() {
    for (auto& play : mPlayer) {
      play.clearMaps();
    }
  }

  bool attack(const sf::Color& col1, int index1);

  bool isGameFinish() const;
  sf::Color getWinner() const;

 private:
  std::vector<std::vector<int>> mMap;
  std::vector<Player> mPlayer;
};

#endif
