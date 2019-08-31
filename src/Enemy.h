/*				Enemy.h
*				Created: 26/05/2015
*				Last Update: 26/05/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Ship.h"

class Enemy : public Ship
{
public:
	Enemy(int healthPoints = 1);
	void update(sf::Time deltaTime) override;
};