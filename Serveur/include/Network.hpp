#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>
#include <iostream>

class Network {
 public:
 	Network( int port );
 	void send(std::string message);
 	void receive();
 	//~Network();
 private:
  sf::TcpListener listener;
  sf::TcpSocket client;
  sf::SocketSelector selector;
  sf::Packet packet;
};

#endif /* NETWORK_HPP */