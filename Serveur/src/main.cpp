#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  sf::RenderWindow window;

  Game g;
  g.loadFile("ressources/level.txt");
  g.addPlayer(sf::Color::Blue, sf::Vector2f(2, 7));
  g.addPlayer(sf::Color::Red, sf::Vector2f(28, 28));

  std::vector<sf::RectangleShape> rects;

  auto map = g.getMap();
  auto n = map.size();
  auto m = map[0].size();
  for (unsigned i{0}; i < n; i++) {
    for (unsigned j{0}; j < m; j++) {
      sf::RectangleShape rect(sf::Vector2f(TILESIZE, TILESIZE));
      if (map[j][i] == 1) rect.setFillColor(sf::Color(70, 190, 70));
      if (map[j][i] == 2) rect.setFillColor(sf::Color(0, 50, 10));
      if (map[j][i] == 3) rect.setFillColor(sf::Color(0, 100, 255));
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

        case sf::Event::KeyPressed:
          std::cout
              << "player ressource : "
              << g.getPlayer(sf::Color::Blue).getRessources(Ressource::Wood)
              << std::endl;
          switch (event.key.code) {
            case sf::Keyboard::Up:
              g.moveEntity(Direction::Up, sf::Color::Blue, 0);
              break;
            case sf::Keyboard::Down:
              g.moveEntity(Direction::Down, sf::Color::Blue, 0);
              break;
            case sf::Keyboard::Left:
              g.moveEntity(Direction::Left, sf::Color::Blue, 0);
              break;
            case sf::Keyboard::Right:
              g.moveEntity(Direction::Right, sf::Color::Blue, 0);
              break;
            case sf::Keyboard::Space:
              g.collectRessource(Direction::Up, sf::Color::Blue, 0);
              break;
            case sf::Keyboard::V:
              g.putRessourcesInTown(Direction::Left, sf::Color::Blue, 0);
              break;
            default:
              break;
          }
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
      sf::RectangleShape r(
          sf::Vector2f(b.getSize().x * TILESIZE, b.getSize().y * TILESIZE));
      r.setFillColor(b.getColor());
      r.setPosition(b.getPosition().x * TILESIZE, b.getPosition().y * TILESIZE);
      window.draw(r);
    }

    auto enttity = g.getEntities();
    for (auto& e : enttity) {
      sf::CircleShape c(TILESIZE / 2);
      c.setFillColor(e.getColor());
      c.setPosition(e.getPosition().x * TILESIZE, e.getPosition().y * TILESIZE);
      window.draw(c);
    }

    window.display();

    g.clearPlayer();
  }
  return 0;
}
