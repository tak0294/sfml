#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <SFML/Graphics.hpp>

/***************************************************************************************
 * InputSystem Class.
 ***************************************************************************************/
class InputSystem {
private:
	static sf::Event event;
public:
	static bool isLeft;
	static bool isRight;
	static bool isUp;
	static bool isDown;
	static bool isA;
	static bool isB;
	static bool isESC;

	static void updateKeyState(sf::RenderWindow &window);
	static void initialize();
};

#endif