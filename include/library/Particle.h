#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "library/Mover.h"

class Particle : public Mover {

	sf::RectangleShape m_shape;
	float m_gravity;
	float m_friction;
	int m_lifeTime;
	sf::Color m_color;

public:
	bool isActive;
	enum ParticleType {
		PARTICLE_CIRCLE = 0,
		PARTICLE_SQUARE = 1,
		PARTICLE_SPRITE = 2,
	};
	ParticleType m_particleType;
	Particle();
	Particle(ParticleType particleType);

	void setColor(sf::Color cl);
	void update();
	void draw();
	void initialize(int x, int y);

};

#endif