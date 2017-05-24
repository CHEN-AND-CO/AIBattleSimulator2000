#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <vector>

int main() {
  unsigned tileSize = 16;
  unsigned size;
  unsigned currentColor = 1;

  std::array<sf::Color, 5> colors = {sf::Color::Black,
                                     sf::Color(70, 190, 70),  // Grass
                                     sf::Color(0, 50, 10),    // Forest
                                     sf::Color(0, 100, 255),  // Water
                                     sf::Color(0, 100, 10)};  // Bush

  std::cout << "Quel est la taille de la map a creer : ";
  std::cin >> size;
  sf::RenderWindow window(sf::VideoMode(size * tileSize, size * tileSize),
                          "MapEditor");

  std::vector<std::vector<int>> map;

  std::vector<std::vector<sf::RectangleShape>> rects;
  for (unsigned i{0}; i < size; i++) {
    map.push_back(std::vector<int>(size));
    rects.push_back(std::vector<sf::RectangleShape>(size));
    for (unsigned j{0}; j < size; j++) {
      sf::RectangleShape tmp(sf::Vector2f(tileSize, tileSize));
      tmp.setPosition(i * tileSize, j * tileSize);
      tmp.setFillColor(colors[currentColor]);
      rects[i][j] = tmp;
    }
  }

  currentColor++;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed: {
          window.close();
        } break;

        case sf::Event::KeyPressed: {
          switch (event.key.code) {
            case sf::Keyboard::Add:
              currentColor++;
              if (currentColor >= colors.size()) {
                currentColor = 0;
              }
              break;

            case sf::Keyboard::Subtract:
              currentColor--;
              if (currentColor < 0) {
                currentColor = colors.size() - 1;
              }
              break;

            case sf::Keyboard::C:
              currentColor = 1;
              for (unsigned i{0}; i < size; i++) {
                for (unsigned j{0}; j < size; j++) {
                  rects[i][j].setFillColor(colors[currentColor]);
                  map[i][j] = currentColor;
                }
              }

            default:
              break;
          }
        } break;

        case sf::Event::MouseButtonPressed: {
          auto tmp = sf::Mouse::getPosition(window);
          auto pos = sf::Vector2f((tmp.x / tileSize) % size,
                                  (tmp.y / tileSize) % size);
          rects[pos.x][pos.y].setFillColor(colors[currentColor]);
          map[pos.x][pos.y] = currentColor;
          std::cout << std::endl
                    << pos.x << " : " << pos.y << std::endl
                    << std::endl
                    << std::endl;
          for (auto& t : map) {
            for (auto& r : t) {
              std::cout << r;
            }
            std::cout << std::endl;
          }
        } break;

        default: { } break; }
    }

    window.clear();
    for (auto& t : rects) {
      for (auto& r : t) {
        window.draw(r);
      }
    }

    window.display();
  }

  return 0;
}