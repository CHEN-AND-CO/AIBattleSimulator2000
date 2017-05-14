#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"
#include "Network.hpp"

int main() {
  sf::RenderWindow window;

  Network networkInterface( 53000 );
  Game g;
  g.loadFile("ressources/level.txt");

  std::vector<sf::RectangleShape> rects;

  auto map = g.getMap();
  auto n = map.size();
  auto m = map[0].size();
  for (unsigned i{0}; i < n; i++) {
    for (unsigned j{0}; j < m; j++) {
      sf::RectangleShape rect(sf::Vector2f(32, 32));
      if (map[j][i] == 1) rect.setFillColor(sf::Color(70, 190, 70));
      if (map[j][i] == 2) rect.setFillColor(sf::Color(0, 50, 10));
      if (map[j][i] == 3) rect.setFillColor(sf::Color(0, 50, 255));
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

    if (selector.wait(sf::milliseconds(10))) {
      networkInterface.receive();
    }

    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }
    window.display();
  }
  return 0;
}
