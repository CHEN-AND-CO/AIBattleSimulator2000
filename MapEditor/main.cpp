#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  unsigned size;
  unsigned currentColor = 1;

  std::array<sf::Color, 5> colors = {sf::Color::Black,
                                     sf::Color(70, 190, 70),  // Grass
                                     sf::Color(0, 50, 10),    // Forest
                                     sf::Color(0, 100, 255),  // Water
                                     sf::Color(0, 100, 10)};  // Bush

  std::cout << "Quel est la taille de la map a creer : ";
  std::cin >> size;
  sf::RenderWindow window(sf::VideoMode(600, 600), "MapEditor");

  unsigned tileSize = 600 / size;

  std::vector<std::vector<int>> map;

  std::vector<std::vector<sf::RectangleShape>> rects;
  for (unsigned i{0}; i < size; i++) {
    map.push_back(std::vector<int>(size));
    rects.push_back(std::vector<sf::RectangleShape>(size));
    for (unsigned j{0}; j < size; j++) {
      sf::RectangleShape tmp(sf::Vector2f(tileSize, tileSize));
      tmp.setPosition(j * tileSize, i * tileSize);
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
              break;

            case sf::Keyboard::S: {
              std::time_t now = std::time(0);

              std::string dt = std::ctime(&now);
              std::replace(dt.begin(), dt.end(), ' ', '_');

              dt = dt.substr(0, dt.size() - 1);

              std::ofstream file(dt + ".txt", std::ios::out);
              file << size << std::endl;

              for (auto& y : map) {
                for (auto& x : y) {
                  file << x << " ";
                }
                file << std::endl;
              }
              break;
            }

            default:
              break;
          }
        } break;

        case sf::Event::MouseButtonPressed: {
          auto tmp = sf::Mouse::getPosition(window);
          auto pos = sf::Vector2f((tmp.x / tileSize) % window.getSize().x,
                                  (tmp.y / tileSize) % window.getSize().y);
          rects[pos.y][pos.x].setFillColor(colors[currentColor]);
          map[pos.y][pos.x] = currentColor;
        } break;

        case sf::Event::MouseMouved: {
          if (sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
              sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto tmp = sf::Mouse::getPosition(window);
            auto pos = sf::Vector2f((tmp.x / tileSize) % window.getSize().x,
                                    (tmp.y / tileSize) % window.getSize().y);
            rects[pos.y][pos.x].setFillColor(colors[currentColor]);
            map[pos.y][pos.x] = currentColor;
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

  std::time_t now = std::time(0);

  std::string dt = std::ctime(&now);
  std::replace(dt.begin(), dt.end(), ' ', '_');

  dt = dt.substr(0, dt.size() - 1);

  std::ofstream file(dt + ".txt", std::ios::out);
  file << size << std::endl;

  for (auto& y : map) {
    for (auto& x : y) {
      file << x << " ";
    }
    file << std::endl;
  }

  return 0;
}