#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Vec2.hpp"
#include "Ray.hpp"
#include "LineSegment.hpp"
#include "Circle.hpp"
#include <vector>

class Renderer {
public:
    Renderer(int width, int height);
    void run();

private:
    sf::RenderWindow window;
    Circle lightSource;
    std::vector<LineSegment> obstacles;
    Circle movingObstacle;
    float moveAngle;
};

#endif
