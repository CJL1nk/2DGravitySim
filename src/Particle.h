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

	float radius;

	sf::Color color = sf::Color::White;
	bool isStatic = false; // Determines whether particle can be moved at all
	bool isMutable = true; // Determines whether particle can be moved by other objects

	static inline const float G = 9.81f;

	Particle(): x(0.0f), y(0.0f), mass(1.0f) {
		radius = 1.0f;
	}
	Particle(float x, float y, float mass): x(x), y(y), mass(mass), radius(mass) {}
	Particle(float x, float y, float mass, bool isStatic): x(x), y(y), mass(mass), radius(mass), isStatic(isStatic) {}
	Particle(float x, float y, float mass, bool isMutable, sf::Color color): x(x), y(y), mass(mass), radius(mass), isMutable(isMutable), color(color) {}
	Particle(float x, float y, float mass, bool isStatic, sf::Color color, float radius): x(x), y(y), mass(mass), radius(radius), isStatic(isStatic), color(color) {}
};

#endif //PARTICLE_H
