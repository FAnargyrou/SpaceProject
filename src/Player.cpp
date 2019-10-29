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
}
void Player::update(sf::Time deltaTime)
{
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
			if (fireDelay.asMilliseconds() > 200)
			{
				FireMissile("missile");
				fireDelay = fireDelay.Zero;
			}
		}
		sprite.move(movement);
		if (IsOffBounds())
		{
			if (sprite.getPosition().x <= 0)
			{
				sprite.setPosition(0, sprite.getPosition().y);
				movement.x = 0;
			}
			if (sprite.getPosition().y <= 0)
			{
				sprite.setPosition(sprite.getPosition().x, 0);
				movement.y = 0;
			}
			if (sprite.getPosition().x >= 800)
			{
				sprite.setPosition(800, sprite.getPosition().y);
				movement.x = 0;
			}
			if (sprite.getPosition().y >= 600)
			{
				sprite.setPosition(sprite.getPosition().x, 600);
				movement.y = 0;
			}
		}
		UpdateImmunity(deltaTime, true);
	}
	else
	{
		ExplodeObject(deltaTime);
	}
	UpdateMissiles();
}