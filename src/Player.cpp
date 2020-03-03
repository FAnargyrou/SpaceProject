/*				Player.cpp
*				Created: 28/02/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Player.h"


Player::Player()
{
	velocity.x = 0.1f;
	velocity.y = 0.1f;
	hitPoints = 3;

	missileMovement.x = 0.0f;
	missileMovement.y = -10.0f;
}
void Player::update(sf::Time deltaTime)
{
	if (hitPoints <= 0)
		bIsDead = true;
	if (!bIsDead)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (movement.y > 0)
				MoveUp();
			MoveUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (movement.y < 0)
				MoveDown();
			MoveDown();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (movement.x > 0)
				MoveLeft();
			MoveLeft();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (movement.x < 0)
				MoveRight();
			MoveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			fireDelay += deltaTime;
			if (fireDelay.asMilliseconds() > 100)
			{
				FireMissile("missile");
				fireDelay = fireDelay.Zero;
			}
		}
		sprite.move(movement);
		Object::update(deltaTime);
		UpdateImmunity(deltaTime, true);
	}
	else
	{
		ExplodeObject(deltaTime);
	}
	UpdateMissiles();
}