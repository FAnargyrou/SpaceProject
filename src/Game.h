/*				Game.h
*				Created: 28/02/2015
*				Last Update: 07/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef GAME_H
#define GAME_H
#include "StateFactory.h"
#include <stdlib.h>

//This is our core class. It handles everything, from textures to player input

class Game
{
public:
	Game();
	//Game base function
	void Run();
private:
	void update(sf::Time deltaTime);
	void render();
	void processEvents();
	
	void RegisterStates();

	sf::RenderWindow window;
	const sf::Time timePerFrame; //Holds time passed. Best used with milliseconds
	sf::View view;

	StateFactory stateFactory;
	sf::Font font;

};
#endif