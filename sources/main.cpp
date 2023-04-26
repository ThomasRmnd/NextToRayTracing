#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "camera/Camera.hpp"
#include "object/Sphere.hpp"
#include "object/Plan.hpp"
#include "object/Cylinder.hpp"
#include "object/Cube.hpp"
#include "random/RandomGenerator.h"
#include "utils/Vec.hpp"
#include "utils/Mat.hpp"

Vec3 get_color(const std::vector<HittableObject*>& objects, const Ray& ray, unsigned int depth) {
    if (depth <= 0) return Vec3::zeros();
    Hit hit_ref;
    for (const HittableObject* object : objects) {
        Hit hit = object->intersect(ray);
        if (hit.getObj() == nullptr) continue;
        if (hit_ref.getObj() == nullptr || hit.getDist() < hit_ref.getDist()) {
            hit_ref = hit;
        }
    }
    if (hit_ref.getObj() != nullptr) {
        Vec3 dir = hit_ref.getNormal() + Vec3::random_unit_ball();
        return 0.5f * get_color(objects, Ray(hit_ref.getPos(), dir), depth - 1);
    }
    Vec3 unit_dir = ray.getDir().normalize();
    float t = 0.5f * (unit_dir.y() + 1.f);
    return ((1.f - t) * Vec3(1.f) + t * Vec3(0.5f, 0.7f, 1.f));
}

sf::Color write_color(const Vec3& color, unsigned int samples_per_pixel) {
    float r = color.x();
    float g = color.y();
    float b = color.z();
    float scale = 1.f / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;
    return sf::Color((sf::Uint8)(255 * std::clamp(r, 0.f, 1.f)), (sf::Uint8)(255 * std::clamp(g, 0.f, 1.f)), (sf::Uint8)(255 * std::clamp(b, 0.f, 1.f)));
}

void lancer0(const std::vector<HittableObject*> objects, Camera* cam, sf::Image& t) {
    unsigned int samples_per_pixel = 2;
    unsigned int max_depth = 5;
    UniformGenerator rand_gen;
    for (unsigned int i = 0; i < cam->getResX(); i++) {
        for (unsigned int j = 0; j < cam->getResY(); j++) {
            Vec3 color(0.f, 0.f, 0.f);
            for (unsigned int k = 0; k < samples_per_pixel; k++) {
                Ray ray = cam->getRay((float)i + rand_gen.generate(), (float)j + rand_gen.generate());
                color += get_color(objects, ray, max_depth);
            }
            t.setPixel(i, cam->getResY() - 1 - j, write_color(color, samples_per_pixel));
        }
    }
    return;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Camera cam_sd(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, -1.f), 300, 200, 10.f, 7.5f, 5.f);
    Sphere sphere_1(Vec3(-5.f, 0.f, -5.f), 2.f);
    Cylinder cylinder_1(Vec3(0.f, 0.f, -5.f), Vec3(1.f, 3.f, 1.f), 1.f, 2.f);
    Cube cube_1(Vec3(5.f, 0.f, -5.f), Vec3(1.f, 1.f, 1.f), 2.f);
    Plan plan_1(Vec3(0.f, -2.f, 0.f), Vec3(0.f, 1.f, 0.f));
    std::vector<HittableObject*> objects = {&plan_1, &sphere_1, &cylinder_1, &cube_1};

    std::cout << "test1" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    std::cout << "test2" << std::endl;
    window.setFramerateLimit(30);
    sf::Image t;
    t.create(cam_sd.getResX(), cam_sd.getResY(), sf::Color::Black);
    sf::Texture texture;
    sf::Sprite sprite;
    lancer0(objects, &cam_sd, t);
    texture.loadFromImage(t);
    sprite.setTexture(texture);
    sprite.setScale(800.f / cam_sd.getResX(), 600.f / cam_sd.getResY());
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        sf::Int32 time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        std::cout << time << std::endl;
        lancer0(objects, &cam_sd, t);
        texture.loadFromImage(t);
        sprite.setTexture(texture);
        sprite.setScale(800.f / cam_sd.getResX(), 600.f / cam_sd.getResY());
        window.draw(sprite);
        window.display();
    }
    return 0;
}