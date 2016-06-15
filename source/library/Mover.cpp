#include "library/Mover.h"
#include "library/Video.h"

Mover::Mover() {
	this->pos = sf::Vector2f();
	this->vel = sf::Vector2f();
	this->scale = sf::Vector2f(1.0f, 1.0f);
	this->rotation = .0f;
	this->drawLayer = Video::SP_1;
}

void Mover::setTexture(std::string texture_filename) {
	this->m_texture.loadFromFile(texture_filename);
	this->m_textureSize = this->m_texture.getSize();
	this->m_sprite.setTexture(this->m_texture);
}

void Mover::draw() {
	this->m_sprite.setPosition(this->pos.x, this->pos.y);
	this->m_sprite.setOrigin(m_textureSize.x/2, m_textureSize.y/2);
	this->m_sprite.setRotation(this->rotation);
	this->m_sprite.setScale(this->scale.x, this->scale.y);
	Video::drawSprite(drawLayer, m_sprite);
	//window.draw(this->m_sprite);
}

void Mover::update() {

}