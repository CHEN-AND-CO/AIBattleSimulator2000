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

  sf::Uint16 x = 10;
  std::string s = "hello";
  double d = 0.6;

  sf::Packet packet;
  packet << x << s << d;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          std::cout<<std::boolalpha<<(socket.send(packet) == sf::Socket::Done)<<std::endl;
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
