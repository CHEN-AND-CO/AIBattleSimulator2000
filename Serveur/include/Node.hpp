#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <vector>

class Node {
 public:
  Node(std::string data, std::vector<std::shared_ptr<Node>> parent)
      : mData{data}, mParent{parent} {}

  void appendChild(std::shared_ptr<Node> node) { mChild.push_back(node); }

  std::string getData() const { return mData; }
  std::vector<std::shared_ptr<Node>> getChild() const { return mChild; }
  std::vector<std::shared_ptr<Node>> getParent() const { return mParent; }

 private:
  std::vector<std::shared_ptr<Node>> mChild;
  std::vector<std::shared_ptr<Node>> mParent;
  std::string mData;
};

bool operator==(const Node& right, const Node& left);
bool operator!=(const Node& right, const Node& left);

#endif