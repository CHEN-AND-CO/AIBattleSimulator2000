#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "Serveur");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  sf::TcpListener listener;

  // bind the listener to a port
  if (listener.listen(53000) != sf::Socket::Done) {
    std::cerr << "Error listener\n";
    return -1;
  }

  char data[100];
  std::size_t received;

  sf::SocketSelector selector;

  sf::TcpSocket client;

  selector.add(client);
  selector.add(listener);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    if (selector.wait(sf::milliseconds(10))) {
      if (selector.isReady(listener)) {
        listener.accept(client);
      } else if (selector.isReady(client)) {
        client.receive(data, 100, received);

        std::cout << "Received " << received << " bytes" << std::endl;
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
