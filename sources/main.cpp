#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils/Vec.hpp"
#include "utils/Mat.hpp"
#include "camera/Camera.hpp"
#include "object/Sphere.hpp"
#include "object/Plan.hpp"
#include "object/Cylinder.hpp"

sf::Image lancer0(const std::vector<HittableObject*> objects, Camera* cam) {
    sf::Image t;
    t.create(cam->getResX(), cam->getResY(), sf::Color::Black);
    for (unsigned int i = 0; i < cam->getResX(); i++) {
        for (unsigned int j = 0; j < cam->getResY(); j++) {
            Ray ray = cam->getRay(i, j);
            const HittableObject* obj = nullptr;
            Vec3 pos;
            for (const HittableObject* o : objects) {
                Hit hit = o->intersect(ray);
                if (hit.getObj() != nullptr) {
                    obj = hit.getObj();
                    Vec3 temp = hit.getPos();
                    if (pos == Vec3(0.f)) {
                        pos = temp;
                    }
                    else {
                        if ((temp - ray.getOrig()).norm2() < (pos - ray.getOrig()).norm2()) {
                            pos = temp;
                        }
                    }
                }
            }
            if (obj != nullptr) {
                Vec3 N = normalize(pos - Vec3(0.f, 0.f, -1.f));
                t.setPixel(i, cam->getResY() - 1 - j, sf::Color((sf::Uint8)(255 * (N.x() + 1.f) / 2.f), (sf::Uint8)(255 * (N.y() + 1.f) / 2.f), (sf::Uint8)(255 * (N.z() + 1.f) / 2.f)));
            }
        }
    }
    return t;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Camera cam_sd(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, -1.f), 300, 200, 6.f, 4.f, 5.f);
    // Sphere sphere_1(Vec3(2.f, 0.f, -5.f), 2.f);
    Cylinder cylinder_1(Vec3(3.f, 0.f, -10.f), Vec3(0.f, 0.f, 1.f), 2.f, 2.f);
    Plan plan_1(Vec3(0.f, -2.f, 0.f), Vec3(0.f, 1.f, 0.f));
    std::vector<HittableObject*> objects = {&cylinder_1, &plan_1};

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(30);
    sf::Image t;
    sf::Texture texture;
    sf::Sprite sprite;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        t = lancer0(objects, &cam_sd);
        texture.loadFromImage(t);
        sprite.setTexture(texture);
        sprite.setScale(800.f / cam_sd.getResX(), 600.f / cam_sd.getResY());
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}