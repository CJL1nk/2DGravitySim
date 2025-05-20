//
// Created by CJ on 5/19/2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
	float x, y; // Position
	float vx = 0, vy = 0; // Velocity
	float ax = 0, ay = 0; // Acceleration

    float mass = 1.0;

	sf::Color color = sf::Color::White;

	static inline const float G = 9.81f;

	Particle(): x(0.0f), y(0.0f), mass(1.0f) {}
	Particle(float x, float y, float mass): x(x), y(y), mass(mass) {}
	Particle(float x, float y, float mass, sf::Color color): x(x), y(y), mass(mass), color(color) {}
};

#endif //PARTICLE_H
