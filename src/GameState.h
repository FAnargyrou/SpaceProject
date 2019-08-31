/*				GameState.h
*				Created: 08/04/2015
*				Last Update: 20/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "ContentLoader.h"

class GameState
{
public:
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	virtual void load() = 0;
	virtual void clean() = 0;
private:
};

#endif