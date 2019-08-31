/*				Asteroid.cpp
*				Created: 01/03/2015
*				Last Update: 02/04/2015
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
		sprite.rotate(0.5f);
		sprite.move(movement);
		if (IsOffBounds())
		{
			if (sprite.getPosition().x > 400)
				SetDirection<mDir::Direction>(mDir::LEFT);
			else
				SetDirection<mDir::Direction>(mDir::RIGHT);
		}
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
		if (size == LARGE)
			scale = 2.f;
		else if (size == SMALL)
			scale = 0.5f;
		else
			scale = 1.f;
		ExplodeObject(deltaTime, scale);
	}
}

bool Asteroid::IsOffBounds()
{
	if (sprite.getPosition().x < 0)
		return true;
	if (sprite.getPosition().x > 800)
		return true;
	return false;
}