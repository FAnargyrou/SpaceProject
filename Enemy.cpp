/*				Enemy.cpp
*				Created: 26/05/2015
*				Last Update: 26/05/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Enemy.h"

Enemy::Enemy(int healthPoints)
{
	maxSpeed = 5.f;
	velocity.x = 0.1;
	velocity.y = 0.1;
	hitPoints = healthPoints;
	size = SMALL;
}

void Enemy::update(sf::Time deltaTime)
{
	if (!bIsDead)
	{
		MoveRight();
		sprite.move(movement);
	}
	else
		explodeObject(deltaTime);
}