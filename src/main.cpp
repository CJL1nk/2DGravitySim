//
// Created by CJ on 5/19/2025.
//

#include <cmath>
#include <iostream>
#include <random>

#include "includes.h"
#include "particle.h"

sf::Color randomColor() {
    sf::Color color;

    color.r = rand() % 255;
    color.g = rand() % 255;
    color.b = rand() % 255;

    return color;
}

void genParticles(std::vector<Particle> &particles, int num_particles) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(100.0f, 1820.0f);
    std::uniform_real_distribution<float> distY(100.0f, 980.0f);
    std::uniform_real_distribution<float> distMass(1.0f, 15.0f);

    for (int i = 0; i < num_particles; ++i) {
        float x = distX(gen);
        float y = distY(gen);
        float mass = distMass(gen);

        particles.emplace_back(x, y, mass, true, randomColor());
    }
}

int main() {
    const float DT = 0.25f;
    const float SOFTENING = 100.f; // make this jawnson bigger if particles are going infinity miles per hour
    std::vector<Particle> particles;

    sf::Vector2u windowSize = sf::Vector2u(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Particle Simulation");
    window.setFramerateLimit(100);

    genParticles(particles, 500);

	Particle THESUN = Particle(960.0f, 540.0f, 500.0f, false, sf::Color(255, 190, 0), 100.f);
	THESUN.isStatic = true;
	particles.push_back(THESUN);

    while (window.isOpen()) {

        for (auto& p : particles) { // Reset particle acceleration
            p.ax = 0;
            p.ay = 0;
        }

       // Calculate forces between particles, VERY unoptimized rn but it works
        for (size_t i = 0; i < particles.size(); ++i) {

        	if (particles[i].isMutable == false) { // Skip to next if current particle is not mutable
        		continue;
        	}

            for (size_t j = 0; j < particles.size(); ++j) {
                if (i == j) continue;

                 Particle& pi = particles[i];
            	 Particle& pj = particles[j];

	             float dx = pj.x - pi.x;
	             float dy = pj.y - pi.y;
	             float distSq = dx * dx + dy * dy + SOFTENING;
	             float dist = std::sqrt(distSq);

	             float force = Particle::G * pi.mass * pj.mass / distSq;

	             float fx = force * (dx / dist);
	             float fy = force * (dy / dist);

	             // Add to acceleration
	             pi.ax += fx / pi.mass;
	             pi.ay += fy / pi.mass;
			}
        }

        // Update velocities and positions
        for (auto& p : particles) {

        	if (p.isStatic == true) { // Don't allow moving of static objects at all
        		continue;
        	}

            p.vx += p.ax * DT;
            p.vy += p.ay * DT;

            p.x += p.vx * DT;
            p.y += p.vy * DT;

            // Keep particles within window
            if (p.x < 0) { p.x = 0; p.vx *= -0.5f; }
            if (p.x > windowSize.x) { p.x = windowSize.x; p.vx *= -0.5f; }
            if (p.y < 0) { p.y = 0; p.vy *= -0.5f; }
            if (p.y > windowSize.y) { p.y = windowSize.y; p.vy *= -0.5f; }
        }

        // Drawing
        window.clear(sf::Color::Black);

        for (const Particle& particle : particles) {

        	sf::CircleShape circle(particle.radius); // Make particles big

        	if (particle.mass != particle.radius) { // If particle radius differs from mass, draw it with a red saturation based on its density (0-255)
        		circle.setFillColor(sf::Color(255, 255.0f - particle.mass, 255.0f - particle.mass));
        	} else {
				circle.setFillColor(particle.color);
        	}

            circle.setPosition(sf::Vector2f(particle.x - particle.radius, particle.y - particle.radius));
            window.draw(circle);
        }

        window.display();

        // Handle events
        while (const std::optional event = window.pollEvent()) {
            // Request for closing the window
            if (event->is<sf::Event::Closed>()) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();

        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { // Press space to make everything crazy
        		std::random_device rd;
        		std::mt19937 gen(rd());
        		std::uniform_int_distribution<> distrib(-10, 10);

        		for (auto& p : particles) {
        			p.vx *= distrib(gen);
        			p.vy *= distrib(gen);
        		}
        	}
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) { // Press space to make everything anti-crazy
        		std::random_device rd;
        		std::mt19937 gen(rd());
        		std::uniform_int_distribution<> distrib(1, 10);

        		for (auto& p : particles) {
        			p.vx /= distrib(gen);
        			p.vy /= distrib(gen);
        		}
        	}
        }
    }

    return 0;
}