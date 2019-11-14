/*				Enemy.cpp
*				Created: 26/05/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Enemy.h"

Enemy::Enemy(int healthPoints)
{
	maxSpeed = 2.f;
	velocity.x = 0.1f;
	velocity.y = 0.1f;

	missileMovement.x = 0.0f;
	missileMovement.y = 10.0f;
}

void Enemy::update(sf::Time deltaTime)
{
	if (hitPoints <= 0)
		bIsDead = true;
	if (!bIsDead)
	{
		switch (pattern)
		{
		case BASIC:
			MoveDown();
			break;

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

		fireDelay += deltaTime;
		if (fireDelay.asMilliseconds() > 500)
		{
			FireMissile("missile");
			fireDelay = fireDelay.Zero;
		}
		sprite.move(movement);
	}
	else
		ExplodeObject(deltaTime);
	UpdateMissiles();
	UpdateImmunity(deltaTime, false);
}