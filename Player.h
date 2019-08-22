/*				Player.h
*				Created: 28/02/2015
*				Last Update: 09/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"
#include "Camera.h"



class Player : public Ship
{
public:
	Player();
	void update(sf::Time deltaTime) override;
private:
	bool isMoving();
};
#endif