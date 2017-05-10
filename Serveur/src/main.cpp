#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
