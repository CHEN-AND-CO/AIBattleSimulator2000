#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  sf::RenderWindow window;

  Game g;
  g.loadFile("ressources/level.txt");
  g.addPlayer(sf::Color::Blue,sf::Vector2f(32*2,32*7));
  g.addPlayer(sf::Color::Red,sf::Vector2f(32*16,32*13));

  std::vector<sf::RectangleShape> rects;

  auto map = g.getMap();
  auto n = map.size();
  auto m = map[0].size();
  for (unsigned i{0}; i < n; i++) {
    for (unsigned j{0}; j < m; j++) {
      sf::RectangleShape rect(sf::Vector2f(32, 32));
      if (map[j][i] == 1) rect.setFillColor(sf::Color(70, 190, 70));
      if (map[j][i] == 2) rect.setFillColor(sf::Color(0, 50, 10));
      if (map[j][i] == 3) rect.setFillColor(sf::Color(0, 100, 255));
      rect.setPosition(sf::Vector2f(i * 32, j * 32));
      rects.push_back(rect);
    }
  }

  window.create(sf::VideoMode(n * 32, m * 32), "Serveur");

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

    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }
    auto buildings = g.getBuildings();
    for (auto& b : buildings) {
      sf::RectangleShape r(b.getSize());
      r.setFillColor(b.getColor());
      r.setPosition(b.getPosition());
      window.draw(r);
    }
    auto enttity = g.getEntities();
    for (auto& e : enttity) {
      sf::CircleShape c(16);
      c.setFillColor(e.getColor());
      c.setPosition(e.getPosition());
      window.draw(c);
    }
    window.display();
  }
  return 0;
}
