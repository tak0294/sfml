#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#include "library/GameManager.h"
#include "scene/TestScene.hpp"
#include "RaceScene.h"

GameManager *gameManager;

/***************************************************************************************
 * Main Func.
 ***************************************************************************************/
int main(int argc, char* argv[]){

	gameManager = new GameManager(WINDOW_WIDTH, WINDOW_HEIGHT);
	RaceScene *s = new RaceScene();
	s->setup();
	gameManager->setScene(s);
	gameManager->start();

	return 0;
}

