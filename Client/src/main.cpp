#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Client.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  Client client("Allah");
  client.connect("127.0.0.1", 53000);

  std::string input,tmp = "";

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          std::getline(std::cin, input);
          client.send(input);
          input.clear();
          break;

        default:
          break;
      }
    }

    client.receive(tmp);
    if( tmp.length() > 0 ){
      std::cout << "SERVER: " << tmp << std::endl;
      tmp.clear();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
