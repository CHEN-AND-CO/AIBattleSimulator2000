#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>

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

  // Create a list to store the future clients
  sf::TcpSocket client;
  // Create a selector
  sf::SocketSelector selector;
  // Add the listener to the selector

  selector.add(listener);

  sf::Uint16 x;
  std::string s;
  double d;

  sf::Packet packet;

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
      if(selector.isReady(listener)){
        if (listener.accept(client) == sf::Socket::Done) {
          std::cout << "New client" << std::endl; 
          selector.add(client);
         }
      }
      else{
        if(selector.isReady(client)){
          if (client.receive(packet) == sf::Socket::Done) {
            packet >> x >> s >> d;
            std::cout<<x<<s<<d<<std::endl;
          }
        }
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
