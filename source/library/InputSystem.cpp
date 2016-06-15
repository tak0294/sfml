#include "library/InputSystem.h"

/**
 * Declare real symbols.
 */
bool InputSystem::isLeft;
bool InputSystem::isRight;
bool InputSystem::isUp;
bool InputSystem::isDown;
bool InputSystem::isA;
bool InputSystem::isB;
bool InputSystem::isESC;
sf::Event InputSystem::event;

void InputSystem::initialize() {
	InputSystem::isLeft = false;
	InputSystem::isRight = false;
	InputSystem::isUp = false;
	InputSystem::isDown = false;
	InputSystem::isA = false;
	InputSystem::isB = false;
	InputSystem::isESC = false;
}

void InputSystem::updateKeyState(sf::RenderWindow &window) {

	if(window.pollEvent(InputSystem::event)){
		switch(InputSystem::event.type){
			case sf::Event::KeyPressed:
				switch(InputSystem::event.key.code){
					case sf::Keyboard::Up:
						InputSystem::isUp = true;
						break;
					case sf::Keyboard::Down:
						InputSystem::isDown = true;
						break;
					case sf::Keyboard::Right:
						InputSystem::isRight = true;
						break;
					case sf::Keyboard::Left:
						InputSystem::isLeft = true;
						break;
					case sf::Keyboard::Escape:
						InputSystem::isESC = true;
						break;
					case sf::Keyboard::Z:
						InputSystem::isA = true;
						break;
					case sf::Keyboard::X:
						InputSystem::isB = true;
						break;
					default:
						break;

				}
			break;

			case sf::Event::KeyReleased:
				switch(InputSystem::event.key.code){
					case sf::Keyboard::Up:
						InputSystem::isUp = false;
						break;
					case sf::Keyboard::Down:
						InputSystem::isDown = false;
						break;
					case sf::Keyboard::Right:
						InputSystem::isRight = false;
						break;
					case sf::Keyboard::Left:
						InputSystem::isLeft = false;
						break;
					case sf::Keyboard::Escape:
						InputSystem::isESC = false;
						break;
					case sf::Keyboard::Z:
						InputSystem::isA = false;
						break;
					case sf::Keyboard::X:
						InputSystem::isB = false;
						break;
					default:
						break;

				}
			break;
		}
	}
}