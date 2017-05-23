#include "IA.hpp"

/**************************************/
/*Calculs des points autour de la case*/
/**************************************/
void IA::computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<sf::Vector2f>& aroundPoints) {
  sf::Vector2f top = pos;
  sf::Vector2f right = pos;
  sf::Vector2f bot = pos;
  sf::Vector2f left = pos;

  top.y--;
  right.x++;
  bot.y++;
  left.x--;

  if (posInMap(game, top)) {
    aroundPoints.push_back(top);
  }
  if (posInMap(game, right)) {
    aroundPoints.push_back(right);
  }
  if (posInMap(game, bot)) {
    aroundPoints.push_back(bot);
  }
  if (posInMap(game, left)) {
    aroundPoints.push_back(left);
  }
}

void IA::computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<Tile>& aroundPoints, const Tile parent,
                       const sf::Vector2f finale) {
  sf::Vector2f top = pos;
  sf::Vector2f right = pos;
  sf::Vector2f bot = pos;
  sf::Vector2f left = pos;
  Tile temp;
  int dist;
  
  temp.parent = std::make_shared<Tile>(parent);

  top.y--;
  right.x++;
  bot.y++;
  left.x--;

  if (posInMap(game, top)) {
  	dist = manhattan(top, finale);
  	temp.strength = dist;
  	temp.position = top;
    aroundPoints.push_back(temp);
  }
  if (posInMap(game, right)) {
    dist = manhattan(right, finale);
  	temp.strength = dist;
  	temp.position = right;
    aroundPoints.push_back(temp);
  }
  if (posInMap(game, bot)) {
    dist = manhattan(bot, finale);
  	temp.strength = dist;
  	temp.position = bot;
    aroundPoints.push_back(temp);
  }
  if (posInMap(game, left)) {
    dist = manhattan(left, finale);
  	temp.strength = dist;
  	temp.position = left;
    aroundPoints.push_back(temp);
  }
}

/*********/
/*Calculs*/
/*********/
int IA::manhattan(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

int IA::manhattan(const sf::Vector2f pos1, const sf::Vector2f pos2) {
  return manhattan(pos1.x, pos1.y, pos2.x, pos2.y);
}

sf::Vector2f IA::minManhattan(const sf::Vector2f pos1, const sf::Vector2f pos2, const sf::Vector2f start) {
  return (manhattan(pos1.x, pos1.y, start.x, start.y) < manhattan(start.x, start.y, pos2.x, pos2.y))?pos1:pos2;
}
