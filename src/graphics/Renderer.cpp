#include "Renderer.hpp"
#include <cmath>

Renderer::Renderer(int width, int height)
    : window(sf::VideoMode(width, height), "Simulador de Fótons em Tempo Real"),
      lightSource(Vec2(width / 2, height / 2), 20.f, sf::Color::Yellow),
      movingObstacle(Vec2(350, 200), 40.f, sf::Color(80, 80, 80)),
      moveAngle(0.0f) {

    window.setFramerateLimit(60);

    obstacles.emplace_back(Vec2(150, 150), Vec2(230, 150));
    obstacles.emplace_back(Vec2(230, 150), Vec2(230, 300));
    obstacles.emplace_back(Vec2(230, 300), Vec2(150, 300));
    obstacles.emplace_back(Vec2(150, 300), Vec2(150, 150));

    obstacles.emplace_back(Vec2(500, 300), Vec2(600, 300));
    obstacles.emplace_back(Vec2(600, 300), Vec2(600, 400));
    obstacles.emplace_back(Vec2(600, 400), Vec2(500, 400));
    obstacles.emplace_back(Vec2(500, 400), Vec2(500, 300));
}

void Renderer::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x >= 0 && mousePos.x < 800 && mousePos.y >= 0 && mousePos.y < 600) {
            lightSource.center = Vec2(mousePos.x, mousePos.y);
        }

        float time = clock.getElapsedTime().asSeconds();
        moveAngle += 0.02f;
        movingObstacle.center.x = 400 + 200 * cos(moveAngle);
        movingObstacle.center.y = 300 + 100 * sin(moveAngle);

        window.clear(sf::Color(20, 20, 20));

        for (const auto& obstacle : obstacles) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(obstacle.p1.x, obstacle.p1.y), sf::Color::White),
                sf::Vertex(sf::Vector2f(obstacle.p2.x, obstacle.p2.y), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        movingObstacle.draw(window);
        lightSource.draw(window);
        window.display();
    }
}
