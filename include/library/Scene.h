#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

/***************************************************************************************
 * Scene Class.
 ***************************************************************************************/
class Scene {
public:
	int frame;
	void setup(){
		frame = 0;
	};
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void update() = 0;
};

#endif