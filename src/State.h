/*				GameState.h
*				Created: 08/04/2015
*				Last Update: 20/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef STATE_H
#define STATE_H
#include "ContentLoader.h"

class State
{
public:
	State() {}
	typedef std::unique_ptr<State> StatePtr;

	virtual bool update(sf::Time deltaTime) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	//virtual void HandleEvent(const sf::Event& event) = 0;

	virtual void load() = 0;
	virtual void clean() = 0;
private:
};

#endif