#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"
#include "Server.hpp"

int main() {
  sf::RenderWindow window;
  unsigned currentId = 0;

<<<<<<< HEAD
  Server server(53000);

  Game g;
  g.loadFile("ressources/level.txt");
=======
  Game game;
  game.loadFile("ressources/level.txt");
  game.addPlayer(sf::Color::Blue, sf::Vector2f(2, 7));
  game.addPlayer(sf::Color::Red, sf::Vector2f(28, 28));
>>>>>>> origin/master

  std::vector<sf::RectangleShape> rects;

  auto map = game.getMap();
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
  std::string input;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
<<<<<<< HEAD
          std::getline(std::cin, input);
          server.send("0", input);
          input.clear();
=======
          switch (event.key.code) {
            case sf::Keyboard::Up:
              game.moveEntity(Direction::Up, sf::Color::Blue, currentId);
              break;

            case sf::Keyboard::Down:
              game.moveEntity(Direction::Down, sf::Color::Blue, currentId);
              break;

            case sf::Keyboard::Left:
              game.moveEntity(Direction::Left, sf::Color::Blue, currentId);
              break;

            case sf::Keyboard::Right:
              game.moveEntity(Direction::Right, sf::Color::Blue, currentId);
              break;

            case sf::Keyboard::Space:
              game.collectRessource(Direction::Up, sf::Color::Blue, currentId);
              game.collectRessource(Direction::Down, sf::Color::Blue,
                                    currentId);
              game.collectRessource(Direction::Left, sf::Color::Blue,
                                    currentId);
              game.collectRessource(Direction::Right, sf::Color::Blue,
                                    currentId);
              break;

            case sf::Keyboard::Return:
              game.putRessourcesInTown(Direction::Up, sf::Color::Blue,
                                       currentId);
              game.putRessourcesInTown(Direction::Down, sf::Color::Blue,
                                       currentId);
              game.putRessourcesInTown(Direction::Left, sf::Color::Blue,
                                       currentId);
              game.putRessourcesInTown(Direction::Right, sf::Color::Blue,
                                       currentId);
              std::cout << "player wood : "
                        << game.getPlayer(sf::Color::Blue)
                               .getRessources(Ressource::Wood)
                        << std::endl;
              break;

            case sf::Keyboard::B:
              game.addBuilding(BuildingType::Fort, sf::Color::Blue, currentId);
              std::cout << "player wood : "
                        << game.getPlayer(sf::Color::Blue)
                               .getRessources(Ressource::Wood)
                        << std::endl;
              break;

            case sf::Keyboard::V:
              game.addEntity(EntityType::Villager, sf::Color::Blue, 0);
              std::cout << "player wood : "
                        << game.getPlayer(sf::Color::Blue)
                               .getRessources(Ressource::Wood)
                        << std::endl;
              break;

            case sf::Keyboard::W:
              game.addEntity(EntityType::Warrior, sf::Color::Blue, 1);
              std::cout << "player wood : "
                        << game.getPlayer(sf::Color::Blue)
                               .getRessources(Ressource::Wood)
                        << std::endl;
              break;

            case sf::Keyboard::A:
              game.attack(sf::Color::Blue, currentId);
              break;

            case sf::Keyboard::Add:
              currentId++;
              if (currentId >=
                  game.getPlayer(sf::Color::Blue).getEntities().size()) {
                currentId = 0;
              }
              break;

            case sf::Keyboard::Subtract:
              currentId--;
              if (currentId < 0) {
                currentId =
                    game.getPlayer(sf::Color::Blue).getEntities().size() - 1;
              }
              break;

            default:
              break;
          }
>>>>>>> origin/master
          break;

        default:
          break;
      }
    }

    server.receive();

    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }
<<<<<<< HEAD
    window.display();
=======

    auto buildings = game.getBuildings();
    for (auto& b : buildings) {
      sf::RectangleShape r(
          sf::Vector2f(b.getSize().x * TILESIZE, b.getSize().y * TILESIZE));
      r.setFillColor(b.getColor());
      r.setPosition(b.getPosition().x * TILESIZE, b.getPosition().y * TILESIZE);
      window.draw(r);
    }

    auto enttity = game.getEntities();
    for (auto& e : enttity) {
      sf::CircleShape c(TILESIZE / 2);
      c.setFillColor(e.getColor());
      c.setPosition(e.getPosition().x * TILESIZE, e.getPosition().y * TILESIZE);
      window.draw(c);
    }

    window.display();

    game.clearPlayer();
>>>>>>> origin/master
  }
  return 0;
}
