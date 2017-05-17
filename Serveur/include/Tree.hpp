#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <vector>

class Node {
 public:
  Node(std::string data) : mData{data} {}

  void appendChild(std::shared_ptr<Node>& node) { mTree.push_back(node); }

  std::string getData() const { return mData; }
  std::vector<std::shared_ptr<Node>> getChild() const { return mTree; }

 private:
  std::vector<std::shared_ptr<Node>> mTree;
  std::string mData;
};

bool operator==(const Node& right, const Node& left);
bool operator!=(const Node& right, const Node& left);

#endif