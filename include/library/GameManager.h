#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include "library/Video.h"
#include "library/InputSystem.h"
#include "library/Scene.h"

/***************************************************************************************
 * GameManager Class.
 ***************************************************************************************/
class GameManager {
	Scene *m_currentScene;
public:
	GameManager(int, int);
	void setScene(Scene *scene);
	void start();
	void quit();
};


#endif