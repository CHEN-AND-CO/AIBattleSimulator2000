#include "Upgrade.hpp"

Upgrade::Upgrade() : root("Debut") {
  // root = Node("Debut");
  root.appendChild(std::make_shared(Node("Fin")));
}
