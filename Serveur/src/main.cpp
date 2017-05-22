#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "GameServer.hpp"
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
int main() {
  //sf::RenderWindow window;

  std::shared_ptr<Game> game = std::make_shared<Game>();
  game->loadFile("ressources/level.txt");

  GameServer gameServer(53000, game);

  //std::vector<sf::RectangleShape> rects;

  auto map = game->getMap();
  /*auto n = map.size();
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
  }*/

  std::cout << gameServer.maptostring(map) << std::endl;

  //window.create(sf::VideoMode(n * 32, m * 32), "Serveur");

  while (true) {
	sleep_for(seconds(1));
    /*sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }*/

    gameServer.receive();
	/*
    window.clear();
    for (auto& r : rects) {
      window.draw(r);
    }
    window.display();*/
  }
  return 0;
}
