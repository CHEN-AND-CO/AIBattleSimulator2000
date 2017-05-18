#include <SFML/Network.hpp>
#include <iostream>

int main() {
  sf::TcpListener listener;
  listener.listen(53013);
  // Wait for a connection
  sf::TcpSocket socket;
  listener.accept(socket);
  std::cout << "New client connected: " << socket.getRemoteAddress()
            << std::endl;
  // Receive a message from the client
  char buffer[1024];
  std::size_t received = 0;
  socket.receive(buffer, sizeof(buffer), received);
  std::cout << "The client said: " << buffer << std::endl;
  // Send an answer
  std::string message = "kevin@terrain:2 1 1 1 1";
  socket.send(message.c_str(), message.size() + 1);

  return 0;
}