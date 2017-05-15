#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"
#include "Server.hpp"

int main() {
  sf::RenderWindow window;

  Server server(53000);

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
  std::string message = "";

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          break;

        default:
          break;
      }
    }

    server.receive(message);
    if( message.length() >0){
      message.clear();
    }

    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }
    window.display();
  }
  return 0;
}
