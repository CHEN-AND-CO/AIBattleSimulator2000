#include "Upgrade.hpp"

Upgrade::Upgrade() : root("Debut") {
  root.appendChild(std::make_shared<Node>(Node("Fin")));
}
