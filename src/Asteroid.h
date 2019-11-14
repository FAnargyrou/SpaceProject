/*				Asteroid.h
*				Created: 01/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef ASTEROID_H
#define ASTEROID_H
#include "Object.h"


class Asteroid : public Object
{
public:
	Asteroid();

	void SetDirection(float i);

	bool IsDivided();
	void SetDivided(bool isDivided);
	virtual void update(sf::Time deltaTime) override;

protected:
	bool bDivided;
};

#endif


