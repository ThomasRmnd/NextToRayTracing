#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils/Vec3.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    Vec3 v3 = v1 + v2;
    std::cout << v1 << " " << v2 << " " << v3 << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(30);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}