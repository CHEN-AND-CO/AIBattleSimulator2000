#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include "GameServer.hpp"

int main() {
  sf::RenderWindow window;

  std::shared_ptr<Game> game = std::make_shared<Game>();

  if (!game->loadFile("ressources/GreatLake.txt")) {
    std::cout << "Error loading file" << std::endl;
    return -1;
  }

  auto map = game->getMap();
  unsigned n = map.size();
  unsigned m = map[0].size();

  game->addPlayer(sf::Color::Blue, sf::Vector2f(2, 7));
  game->addPlayer(sf::Color::Red, sf::Vector2f(28, 28));
  GameServer gameServer(53000, game);

  std::vector<sf::RectangleShape> rects;

  for (unsigned i{0}; i < n; i++) {
    for (unsigned j{0}; j < m; j++) {
      sf::RectangleShape rect(sf::Vector2f(TILESIZE, TILESIZE));
      if (map[j][i] == 1) rect.setFillColor(sf::Color(70, 190, 70));
      if (map[j][i] == 2) rect.setFillColor(sf::Color(0, 50, 10));
      if (map[j][i] == 3) rect.setFillColor(sf::Color(0, 100, 255));
      if (map[j][i] == 4) rect.setFillColor(sf::Color(0, 100, 10));
      if (map[j][i] == 5) rect.setFillColor(sf::Color(193, 172, 81));
      rect.setPosition(sf::Vector2f(i * TILESIZE, j * TILESIZE));
      rects.push_back(rect);
    }
  }

  window.create(sf::VideoMode(n * TILESIZE, m * TILESIZE), "Serveur");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    gameServer.receive();

    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }

    auto buildings = game->getBuildings();
    for (auto& b : buildings) {
      sf::RectangleShape r(
          sf::Vector2f(b.getSize().x * TILESIZE, b.getSize().y * TILESIZE));
      r.setFillColor(b.getColor());
      r.setPosition(b.getPosition().x * TILESIZE, b.getPosition().y * TILESIZE);
      window.draw(r);
    }

    auto enttity = game->getEntities();
    for (auto& e : enttity) {
      sf::CircleShape c(TILESIZE / 2);
      c.setFillColor(e.getColor());
      c.setPosition(e.getPosition().x * TILESIZE, e.getPosition().y * TILESIZE);
      window.draw(c);
    }

    window.display();

    game->updateCachePlayer();
    game->clearPlayer();
  }

  return 0;
}
