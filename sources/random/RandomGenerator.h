#pragma once

#include <random>

class RandomGenerator {

public:

    virtual float generate() = 0;

};

class UniformGenerator : public RandomGenerator {

private:

    std::mt19937 m_generator;
    std::uniform_real_distribution<float> m_distribution;

public:

    UniformGenerator() : 
        m_generator(std::random_device()()),
        m_distribution(0.f, 1.f)
    {}

    float generate() override {
        return m_distribution(m_generator);
    };

    float generate(float min, float max) {
        return min + (max - min) * generate();
    }

};