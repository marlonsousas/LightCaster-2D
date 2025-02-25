#include "Circle.hpp"

void Circle::draw(sf::RenderWindow& window) const {
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(center.x - radius, center.y - radius);
    window.draw(shape);
}
