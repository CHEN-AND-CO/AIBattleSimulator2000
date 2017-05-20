#include "Client.hpp"
#include "Define.hpp"

sf::Socket::Status Client::connect(const sf::IpAddress& IP,
                                   unsigned short port) {
  sf::Socket::Status stat = mSocket.connect(IP, port);
  mSocket.setBlocking(false);

  std::string data;
  while ((data = receive()) == "Error") {
  }

  data = getData(data).second.second;

  send(data + "@auth:1 " + mName);
  return stat;
}

sf::Socket::Status Client::send(const std::string& msg) {
  return mSocket.send(msg.c_str(), msg.length());
}

std::string Client::receive() {
  char buffer[MAX_NET_BUFFER_LENGTH];
  size_t length;
  std::string msg = "Error";
  sf::Socket::Status status =
      mSocket.receive(buffer, MAX_NET_BUFFER_LENGTH, length);
  if (status == sf::Socket::Done) {
    msg = buffer;
  }
  return msg;
}
