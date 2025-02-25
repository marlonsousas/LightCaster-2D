#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

// Estrutura para representar um ponto 2D
struct Vec2 {
    float x, y;

    Vec2(float x = 0, float y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(float f) const { return Vec2(x * f, y * f); }

    float dot(const Vec2& v) const { return x * v.x + y * v.y; }
    float cross(const Vec2& v) const { return x * v.y - y * v.x; }

    float length() const { return sqrt(x * x + y * y); }

    Vec2 normalize() const {
        float l = length();
        if (l < 0.0001f) return Vec2(0, 0);
        return Vec2(x / l, y / l);
    }
};

// Estrutura para representar um raio 2D
struct Ray {
    Vec2 origin;
    Vec2 direction;

    Ray(const Vec2& o, const Vec2& d) : origin(o), direction(d.normalize()) {}
};

// Estrutura para representar um segmento de linha (obstáculo)
struct LineSegment {
    Vec2 p1, p2;

    LineSegment(const Vec2& start, const Vec2& end) : p1(start), p2(end) {}

    // Verificar interseção com um raio
    bool intersect(const Ray& ray, float& t) const {
        Vec2 v1 = ray.origin - p1;
        Vec2 v2 = p2 - p1;
        Vec2 v3(-ray.direction.y, ray.direction.x);

        float dot = v2.dot(v3);
        if (std::abs(dot) < 0.0001f)
            return false;

        float t1 = v2.cross(v1) / dot;
        float t2 = v1.dot(v3) / dot;

        if (t1 >= 0.0f && t2 >= 0.0f && t2 <= 1.0f) {
            t = t1;
            return true;
        }
        return false;
    }
};

// Estrutura para representar um círculo (fonte de luz)
struct Circle {
    Vec2 center;
    float radius;
    sf::Color color;

    Circle(const Vec2& c, float r, const sf::Color& col) : center(c), radius(r), color(col) {}

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape shape(radius);
        shape.setFillColor(color);
        shape.setPosition(center.x - radius, center.y - radius);
        window.draw(shape);
    }
};

int main() {
    // Configurações da janela
    const int WIDTH = 800;
    const int HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Simulador de fótons em tempo real");
    window.setFramerateLimit(60);

    // Fonte de luz (círculo)
    Circle lightSource(Vec2(WIDTH / 2, HEIGHT / 2), 20.f, sf::Color::Yellow);

    // Número de raios emitidos pela fonte de luz
    const int NUM_RAYS = 360*5;

    std::vector<LineSegment> obstacles;

    sf::RectangleShape rectangle1(sf::Vector2f(80, 150));
    rectangle1.setPosition(150, 150);
    rectangle1.setFillColor(sf::Color(100, 100, 100));

    sf::RectangleShape rectangle2(sf::Vector2f(100, 100));
    rectangle2.setPosition(500, 300);
    rectangle2.setFillColor(sf::Color(100, 100, 100));

    auto addRectangleObstacles = [&obstacles](const sf::RectangleShape& rect) {
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;
        float w = rect.getSize().x;
        float h = rect.getSize().y;

        obstacles.push_back(LineSegment(Vec2(x, y), Vec2(x + w, y)));
        obstacles.push_back(LineSegment(Vec2(x + w, y), Vec2(x + w, y + h)));
        obstacles.push_back(LineSegment(Vec2(x + w, y + h), Vec2(x, y + h)));
        obstacles.push_back(LineSegment(Vec2(x, y + h), Vec2(x, y)));
    };

    addRectangleObstacles(rectangle1);
    addRectangleObstacles(rectangle2);

    // Círculo móvel adicional (obstáculo)
    Circle movingObstacle(Vec2(350, 200), 40.f, sf::Color(80, 80, 80));
    float moveAngle = 0.0f;

    // Loop principal
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // MODIFICAÇÃO PRINCIPAL: Mover a fonte de luz diretamente para a posição do mouse
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Verificar se o mouse está dentro da janela
        if (mousePos.x >= 0 && mousePos.x < WIDTH && mousePos.y >= 0 && mousePos.y < HEIGHT) {
            lightSource.center = Vec2(mousePos.x, mousePos.y);
        }

        // Atualizar posição do obstáculo móvel
        float time = clock.getElapsedTime().asSeconds();
        moveAngle += 0.02f;
        movingObstacle.center.x = WIDTH / 2 + 200 * cos(moveAngle);
        movingObstacle.center.y = HEIGHT / 2 + 100 * sin(moveAngle);

        // Limpar a tela
        window.clear(sf::Color(20, 20, 20));

        // Desenhar os raios de luz
        for (int i = 0; i < NUM_RAYS; i++) {
            float angle = (float)i * 2 * M_PI / NUM_RAYS;
            Vec2 direction(cos(angle), sin(angle));
            Ray ray(lightSource.center, direction);

            // Encontrar a interseção mais próxima
            float minT = INFINITY;
            bool hasHit = false;

            for (const auto& obstacle : obstacles) {
                float t;
                if (obstacle.intersect(ray, t) && t < minT) {
                    minT = t;
                    hasHit = true;
                }
            }

            // Verificar colisão com o obstáculo circular móvel
            Vec2 oc = ray.origin - movingObstacle.center;
            float a = ray.direction.dot(ray.direction);
            float b = 2.0f * oc.dot(ray.direction);
            float c = oc.dot(oc) - movingObstacle.radius * movingObstacle.radius;
            float discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                float sqrtd = sqrt(discriminant);
                float t1 = (-b - sqrtd) / (2.0f * a);

                if (t1 > 0.001f && t1 < minT) {
                    minT = t1;
                    hasHit = true;
                }
            }

            // Desenhar o raio
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(ray.origin.x, ray.origin.y);
            line[0].color = sf::Color::Yellow;

            if (hasHit) {
                Vec2 hitPoint = ray.origin + ray.direction * minT;
                line[1].position = sf::Vector2f(hitPoint.x, hitPoint.y);
            } else {
                // Se não houver obstáculo, o raio vai até o limite da tela
                Vec2 farPoint = ray.origin + ray.direction * 2000.0f;
                line[1].position = sf::Vector2f(farPoint.x, farPoint.y);
            }
            line[1].color = sf::Color(255, 255, 0, 100);

            window.draw(line, 2, sf::Lines);
        }

        // Desenhar os obstáculos
        for (const auto& obstacle : obstacles) {
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(obstacle.p1.x, obstacle.p1.y);
            line[0].color = sf::Color::White;
            line[1].position = sf::Vector2f(obstacle.p2.x, obstacle.p2.y);
            line[1].color = sf::Color::White;

            window.draw(line, 2, sf::Lines);
        }

        // Desenhar os retângulos
        window.draw(rectangle1);
        window.draw(rectangle2);

        // Desenhar o obstáculo circular móvel
        movingObstacle.draw(window);

        // Desenhar a fonte de luz
        lightSource.draw(window);

        // Desenhar instruções
        sf::Font font;
        if (font.loadFromFile("src/assets/fonts/Arial.ttf")) {  // Certifique-se de ter um arquivo de fonte disponível
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setCharacterSize(14);
            instructions.setFillColor(sf::Color::White);
            instructions.setPosition(10, 10);
            instructions.setString("Mova o mouse para controlar a fonte de luz");
            window.draw(instructions);
        }

        window.display();
    }

    return 0;
}