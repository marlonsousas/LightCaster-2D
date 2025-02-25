#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Vec2.hpp"
#include <SFML/Graphics.hpp>

struct Circle {
    Vec2 center;
    float radius;
    sf::Color color;

    Circle(const Vec2& c, float r, const sf::Color& col) : center(c), radius(r), color(col) {}

    void draw(sf::RenderWindow& window) const;
};

#endif
