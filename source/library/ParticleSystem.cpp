#include "library/ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	m_maxParticleNum = DEFAULT_PARTICLE_NUM;
	initialize();
}

ParticleSystem::ParticleSystem(int maxParticleNum) {
	m_maxParticleNum = maxParticleNum;
	initialize();
}

void ParticleSystem::initialize() {
	
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		Particle *p = new Particle();
		m_particles.push_back(p);
	}
}

void ParticleSystem::addColor(sf::Color cl) {
	m_colors.push_back(cl);
}

void ParticleSystem::draw() {
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(m_particles.at(ii)->isActive) {
			m_particles.at(ii)->draw();
		}
	}
 }


void ParticleSystem::update() {
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(m_particles.at(ii)->isActive) {
			m_particles.at(ii)->update();
		}
	}
}

void ParticleSystem::add(int x, int y) {
	int makeAtOnce = 5;
	int makeCount = 0;
	for(int ii=0;ii<m_maxParticleNum;ii++) {
		if(!m_particles.at(ii)->isActive) {
			m_particles.at(ii)->initialize(x, y);
			if(m_colors.size() > 0) {
				int color_key = rand() % m_colors.size();
				m_particles.at(ii)->setColor(m_colors[color_key]);
			}
			makeCount++;
			if(makeCount == makeAtOnce) {
				break;
			}
		}
	}
}