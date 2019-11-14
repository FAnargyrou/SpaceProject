/*				Asteroid.cpp
*				Created: 01/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Asteroid.h"

Asteroid::Asteroid() : bDivided(false)
{

}

bool Asteroid::IsDivided()
{
	return bDivided;
}

void Asteroid::SetDivided(bool isDivided)
{
	bDivided = isDivided;
}

void Asteroid::update(sf::Time deltaTime)
{
	//TO DO:
	if (!bIsDead)
	{
		Object::update(deltaTime);
		sprite.rotate(0.5f);
		sprite.move(movement);

		if (bIsHit)
		{
			lastFrame += deltaTime;
			if (lastFrame.asMilliseconds() >= 100)
			{
				sprite.setColor(sf::Color(255, 255, 255, 255));
				lastFrame = lastFrame.Zero;
				bIsHit = false;
			}
		}
		UpdateImmunity(deltaTime);
	}
	else
	{
		float scale;
		if (size >= 30)
			scale = 2.f;
		else if (size <= 10)
			scale = 0.5f;
		else
			scale = 1.f;
		ExplodeObject(deltaTime, scale);
	}
}

void Asteroid::SetDirection(float i)
{
	movement.x = i;
}