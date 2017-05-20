#include "Define.hpp"

std::pair<std::string, std::pair<unsigned, std::string>> getData(
    const std::string& input) {
  std::pair<std::string, std::pair<unsigned, std::string>> output;

  std::string data = input;
  data = data.substr(data.find('@') + 1);  // delete the l'id

  output.first = data.substr(0, data.find(':'));  // get the command
  data = data.substr(data.find(':') + 1);

  output.second.first = std::stoi(data.substr(0, 1));  // get the number of arg
  data = data.substr(2);

  output.second.second = data; //get the arguments

  return output;
}
