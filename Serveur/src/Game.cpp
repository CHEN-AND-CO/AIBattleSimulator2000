#include "Game.hpp"
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

bool Game::isGameFinish() const {
  sf::Color tmp = mBuilding[0].getColor();
  for (const auto& b : mBuilding) {
    if (b.getColor() != tmp) {
      return false;
    }
  }
  return true;
}

sf::Color Game::getWinner() const {
  if (isGameFinish()) {
    return mBuilding[0].getColor();
  }
  return sf::Color::Black;
}
