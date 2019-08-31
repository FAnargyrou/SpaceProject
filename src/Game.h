/*				Game.h
*				Created: 28/02/2015
*				Last Update: 07/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef GAME_H
#define GAME_H
#include "PlayState.h"
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

	sf::RenderWindow window;
	sf::Sprite test;
	const sf::Time timePerFrame; //Holds time passed. Best used with milliseconds
	sf::View view;

	PlayState play;


};
#endif