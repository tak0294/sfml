#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "library/Particle.h"

const int DEFAULT_PARTICLE_NUM = 256;

class ParticleSystem {
private:
	int m_maxParticleNum;
	std::vector<Particle*> m_particles;
	std::vector<sf::Color> m_colors;

public:
	ParticleSystem();
	ParticleSystem(int maxParticleNum);
	void initialize();
	void addColor(sf::Color cl);
	void draw();
	void update();
	void add(int x, int y);
};

#endif