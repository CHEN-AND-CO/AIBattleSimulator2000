#include "Client.hpp"
#include "Define.hpp"

sf::Socket::Status Client::connect(const sf::IpAddress& IP, unsigned short port,
                                   const sf::Color& col) {
  sf::Socket::Status stat = mSocket.connect(IP, port);
  mSocket.setBlocking(false);

  std::string data;
  while ((data = receive()) == "Error") {
  }

  data = getData(data).second.second;

  send(data + "@auth:1 " + mName + " " + std::to_string(col.r) + " " +
       std::to_string(col.g) + " " + std::to_string(col.b));

  while ((data = receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "auth") {
    std::cout << "Wrong command received" << std::endl;
    std::cout << "Received " << data << std::endl;
  }

  if (datas.second.second != "ok") {
    return sf::Socket::Error;
  }

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
