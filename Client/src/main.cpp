#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "Client");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  sf::TcpSocket socket;
  sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
  if (status != sf::Socket::Done) {
    std::cerr << "Error open tcp\n";
    return -1;
  }

  char data[100] = "Hello";

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          socket.send(data, 100);
          break;

        default:
          break;
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
