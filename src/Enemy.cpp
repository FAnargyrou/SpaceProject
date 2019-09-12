/*				Enemy.cpp
*				Created: 26/05/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Enemy.h"

Enemy::Enemy(int healthPoints)
{
	maxSpeed = 5.f;
	velocity.x = 0.1f;
	velocity.y = 0.1f;
	hitPoints = healthPoints;
}

void Enemy::update(sf::Time deltaTime)
{
	if (!bIsDead)
	{
		MoveRight();
		sprite.move(movement);
	}
	else
		ExplodeObject(deltaTime);
}