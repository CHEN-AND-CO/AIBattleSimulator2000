#include "Tree.hpp"

bool operator==(const Node& right, const Node& left) {
  return right.getData() == left.getData();
}

bool operator!=(const Node& right, const Node& left) {
  return !(right == left);
}
