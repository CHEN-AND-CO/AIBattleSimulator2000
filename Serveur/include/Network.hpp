#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>
#include <iostream>

class Network {
 public:
 	Network( const int port );
 	void send(const std::string message);
 	void receive();
 	sf::SocketSelector getSelector();
 	//~Network();
 private:
  sf::TcpListener listener;
  sf::TcpSocket client;
  sf::SocketSelector selector;
  sf::Packet packet;
};

#endif /* NETWORK_HPP */