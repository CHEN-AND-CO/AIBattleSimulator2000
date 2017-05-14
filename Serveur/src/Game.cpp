#include "Game.hpp"
#include <algorithm>
#include <iostream>

bool Game::loadFile(const std::string& fileName) {
  std::ifstream file(fileName, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error open file " << fileName << std::endl;
    return false;
  }
  int n, tmp;
  file >> n;
  for (int i{0}; i < n; i++) {
    mMap.push_back(std::vector<int>(n));
    for (int j{0}; j < n; j++) {
      file >> tmp;
      mMap[i][j] = tmp;
    }
  }
  return true;
}

bool Game::isGameFinish() const { return mPlayer.size() == 1; }

sf::Color Game::getWinner() const {
  if (isGameFinish()) {
    return mPlayer[0].getColor();
  }
  return sf::Color::Black;
}

std::vector<Building> Game::getBuildings() const {
  std::vector<Building> v;
  for (const auto& player : mPlayer) {
    v.insert(v.end(), player.getBuildings().begin(),
             player.getBuildings().end());
  }
  return v;
}

std::vector<Entity> Game::getEntities() const {
  std::vector<Entity> v;
  for (const auto& player : mPlayer) {
    v.insert(v.end(), player.getEntities().begin(), player.getEntities().end());
  }
  return v;
}
