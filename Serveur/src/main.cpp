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
  std::list<sf::TcpSocket*> clients;
  // Create a selector
  sf::SocketSelector selector;
  // Add the listener to the selector
  selector.add(listener);

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

    if (selector.wait(sf::seconds(1))) {
      // Test the listener
      if (selector.isReady(listener)) {
        // The listener is ready: there is a pending connection
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done) {
          // Add the new client to the clients list
          clients.push_back(client);
          // Add the new client to the selector so that we will
          // be notified when he sends something
          selector.add(*client);
        } else {
          // Error, we won't get a new connection, delete the socket
          delete client;
        }
      } else {
        // The listener socket is not ready, test all other sockets (the
        // clients)
        for (std::list<sf::TcpSocket*>::iterator it = clients.begin();
             it != clients.end(); ++it) {
          sf::TcpSocket& client = **it;
          if (selector.isReady(client)) {
            // The client has sent some data, we can receive it
            if (client.receive(packet) == sf::Socket::Done) {
              packet >> x >> s >> d;
              std::cout<<x<<s<<d<<std::endl;
            }
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
