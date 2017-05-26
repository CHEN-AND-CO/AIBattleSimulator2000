#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INFOS_TILESIZE 60
#define INFOS_TILESPACE 10

int main() {
  unsigned size;
  unsigned currentColor = 1;
  unsigned tempColor = 1, k, l;
  
  sf::Font font;
	font.loadFromFile("arial.ttf");

  std::array<sf::Color, 5> colors = {sf::Color::Black,
                                     sf::Color(70, 190, 70),  // Grass
                                     sf::Color(0, 50, 10),    // Forest
                                     sf::Color(0, 100, 255),  // Water
                                     sf::Color(0, 100, 10)};  // Bush

  std::array<std::string, 5> colorsName = {"error",
                                     "Grass",  // Grass
                                     "Forest",    // Forest
                                     "Water",  // Water
                                     "Bush"};  // Bush

  std::cout << "Quel est la taille de la map a creer : ";
  std::cin >> size;
  sf::RenderWindow infos(sf::VideoMode(400, 400), "MapEditor - Infos");
  sf::RenderWindow window(sf::VideoMode(600, 600), "MapEditor");
  
  infos.setPosition(sf::Vector2i(0, 0));
  window.setPosition(sf::Vector2i(infos.getSize().x, 0));

  unsigned tileSize = 600 / size;
  
  infos.setSize(sf::Vector2u(300, (INFOS_TILESIZE + INFOS_TILESPACE*2)*(colors.size()-1)));

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
  
  for (unsigned i{0}; i < size; i++) {
    for (unsigned j{0}; j < size; j++) {
      map[i][j] = currentColor-1;
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    sf::Event event2;
    while (window.pollEvent(event) || infos.pollEvent(event2)) {
    	if(event2.type == sf::Event::Closed){}
      switch (event.type) {
        case sf::Event::Closed: {
        	infos.close();
          window.close();
        } break;

        case sf::Event::KeyPressed: {
          switch (event.key.code) {
            case sf::Keyboard::Add:
              currentColor++;
              if (currentColor >= colors.size()) {
                currentColor = 1;
              }
              break;

            case sf::Keyboard::Subtract:
              currentColor--;
              if (currentColor < 1) {
                currentColor = colors.size() - 1;
              }
              break;

            case sf::Keyboard::C:
            	tempColor = currentColor;
              currentColor = 1;
              for (unsigned i{0}; i < size; i++) {
                for (unsigned j{0}; j < size; j++) {
                  rects[i][j].setFillColor(colors[currentColor]);
                  map[i][j] = currentColor;
                }
              }
            	currentColor = tempColor;
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

        case sf::Event::MouseMoved: {
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
    infos.clear();
    for (auto& t : rects) {
      for (auto& r : t) {
        window.draw(r);
      }
    }
    
   	sf::Text text;
    for (k = INFOS_TILESPACE, l = 1; l < colors.size(); k += INFOS_TILESIZE + INFOS_TILESPACE, l++){
    	sf::RectangleShape rect(sf::Vector2f(INFOS_TILESIZE, INFOS_TILESIZE));
      rect.setPosition(5, k);
      rect.setFillColor(colors[l]);

			text.setFont(font);
			text.setString(colorsName[l]);
			text.setCharacterSize(24);
			text.setColor(sf::Color::White);
      text.setPosition(rect.getPosition().x*2 + INFOS_TILESIZE, k + INFOS_TILESIZE/2 - text.getCharacterSize()/2);
      
      if(currentColor == l){
      	rect.setOutlineThickness(INFOS_TILESPACE/2);
				rect.setOutlineColor(sf::Color(255, 255, 0));
      }
      
      infos.draw(rect);
      infos.draw(text);
    }
    
    text.setFont(font);
		text.setString("'C' : Clear\n'+/-' : Change color\n'S' : Save changes");
		text.setCharacterSize(24);
		text.setColor(sf::Color::White);
    text.setPosition(5, k + INFOS_TILESIZE/2 - text.getCharacterSize()/2);
    infos.draw(text);

		infos.display();
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
