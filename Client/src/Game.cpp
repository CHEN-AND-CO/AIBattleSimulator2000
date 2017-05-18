#include "Game.hpp"

Game::Game(const sf::IpAddress& ip, unsigned short port, std::string name)
    : mClient(name) {
  mClient.connect(ip, port);
}

std::vector<std::vector<int>> Game::getMap() {
  std::string data;
  std::vector<std::vector<int>> v;
  unsigned n = 0;

  // mClient.send(mClient.getName() + "@getTerrainMap:0");

  // while ((data = mClient.receive()) == "Error") {
  // }*
  data = "kevin@terrain:4 1 1 1 1";

  data = data.substr(data.find('@') + 1);

  if (data.substr(0, data.find(':')) != "terrain") {
    return v;
  }

  data = data.substr(data.find(':') + 1);

  n = std::sqrt(std::stoi(data.substr(0, 1)));

  if (n == 0) {
    return v;
  }

  data = data.substr(2);

  for (unsigned i{0}; i < n; i++) {
    v.push_back(std::vector<int>(n));
    for (unsigned j{0}; j < n; j++) {
      v[i][j] = std::stoi(data.substr(0, 1));
      data = data.substr(data.find(' ', 1) + 1);
    }
  }

  return v;
}