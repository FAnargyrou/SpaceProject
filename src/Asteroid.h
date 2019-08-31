/*				Asteroid.h
*				Created: 01/03/2015
*				Last Update: 23/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef ASTEROID_H
#define ASTEROID_H
#include "Object.h"


	//To differ the 3 sizes of asteroids (Large, medium or small)

class Asteroid : public Object
{
public:
	Asteroid();

	template<typename DIR>
	void SetDirection(DIR dir);

	bool IsDivided();
	void SetDivided(bool isDivided);
	void SetOppositeDirection();
	virtual void update(sf::Time deltaTime) override;

	virtual bool IsOffBounds() override;

protected:
	bool bDivided;
};

#endif

template<typename DIR>
void Asteroid::SetDirection(DIR dir)
{
	if (dir == mDir::LEFT)
		movement.x = -1.f;
	else if (dir == mDir::RIGHT)
		movement.x = 1.f;
	else
		movement.x = 0.f;
}