/*				Ship.cpp
*				Created: 07/03/2015
*				Last Update: 07/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Ship.h"

Ship::Ship() : fireDelay(sf::Time::Zero)
{
	velocity.x = -0.1f;
	velocity.y = -0.1f;
}

std::vector<sf::Sprite> Ship::GetMissiles()
{
	return missiles;
}

sf::Sprite Ship::getMissileSprite(int index)
{
	return missiles[index];
}

void Ship::DestroyMissile(int index)
{
	missiles.erase(missiles.begin() + index);
}

void Ship::FireMissile(std::string texture, mDir::Direction dir)
{
	sf::Sprite missile;
	missile.setTexture((ContentManager::Instance().get(texture)));
	missile.setPosition(sf::Vector2f(sprite.getPosition()));
	missiles.push_back(missile);
}

void Ship::MoveUp()
{
	if (maxSpeed == 0)
		movement.y -= velocity.y;
	else
		if (movement.y >= (maxSpeed * -1))
			movement.y -= velocity.y;
}
void Ship::MoveDown()
{
	if (maxSpeed == 0)
		movement.y += velocity.y;
	else
		if (movement.y <= maxSpeed)
			movement.y += velocity.y;
}
void Ship::MoveLeft()
{
	if (maxSpeed == 0)
		movement.x -= velocity.x;
	else
		if (movement.x >= (maxSpeed * -1))
			movement.x -= velocity.x;
}
void Ship::MoveRight()
{
	if (maxSpeed == 0)
		movement.x += velocity.x;
	else
		if (movement.x <= maxSpeed)
			movement.x += velocity.x;
}

void Ship::Stop()
{
	if (movement.x != 0 || movement.y != 0)
	{
		if (movement.x > 0)
			movement.x -= velocity.x;
		else
			movement.x += velocity.x;
		if (movement.y > 0)
			movement.y -= velocity.y;
		else
			movement.y += velocity.y;
		if (movement.x <= 0.2f && movement.x >= -0.2f)
			movement.x = 0;
		if (movement.y <= 0.2f && movement.y >= -0.2f)
			movement.y = 0;
	}
}

void Ship::UpdateMissiles()
{
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i].move(0, -10.f);
		if (missiles[i].getPosition().x > 800 || missiles[i].getPosition().x < 0 || missiles[i].getPosition().y > 600 || missiles[i].getPosition().y < 0)
			DestroyMissile(i);
	}
}

void Ship::SetMaxSpeed(float speed)
{
	maxSpeed = speed;
}