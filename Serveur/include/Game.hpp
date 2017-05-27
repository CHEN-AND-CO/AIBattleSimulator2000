#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Player.hpp"


class Game {
 public:
  Game();
  bool loadFile(const std::string& fileName);
  std::vector<Player> getPlayer() const { return mPlayer; }
  Player getPlayer(const sf::Color&) const;

  std::vector<std::vector<int>> getMap() const { return mMap; }
  std::vector<Building> getBuildings() const;
  std::vector<Entity> getEntities() const;

  std::vector<std::vector<int>> getVisibleMap(const sf::Color& col) const;
  std::vector<Building> getVisibleBuildings(const sf::Color& col) const;
  std::vector<Entity> getVisibleEntities(const sf::Color& col) const;
  std::vector<Building> getBuildings(const sf::Color&) const;
  std::vector<Entity> getEntities(const sf::Color&) const;

  bool addEntity(const EntityType& entT, const sf::Color& col, int index) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addEntity(*this, entT, index, mEntityCost);
        return true;
      }
    }
    return false;
  }

  bool addBuilding(const BuildingType& buildT, const sf::Color& col,
                   int index) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        player.addBuilding(*this, buildT, index, mBuildingCost);
        return true;
      }
    }
    return false;
  }

  bool addPlayer(const sf::Color& col, const sf::Vector2f pos) {
    for (auto& player : mPlayer) {
      if (player.getColor() == col) {
        return false;
      }
    }
    mPlayer.push_back(
        Player(*this, col, pos, mBuildingCost, mEntityCost, mMap.size()));
    return true;
  }

  bool attack(const sf::Color& col1, int index1, const Direction& dir);
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

  void clearPlayer();
  void updateCachePlayer() {
    for (auto& play : mPlayer) {
      play.updateCache();
    }
  }

  bool isGameFinish() const { return mPlayer.size() == 1; }
  sf::Color getWinner() const;

 private:
  buildMap mBuildingCost;
  entMap mEntityCost;
  std::vector<std::vector<int>> mMap;
  std::vector<Player> mPlayer;
};

#endif
