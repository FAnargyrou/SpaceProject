/*				Object.cpp
*				Created: 28/02/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Object.h"

std::string Object::explosionID = "explosion";

Object::Object()
{
	bIsDead = false;
	bIsExploding = false;
	bIsHit = false;
	bIsImmune = false;
}

//Before definition
void Object::load(std::string id, sf::Vector2f position, bool bLoadRect)
{
	
	sprite.setTexture(Content::Instance().get(id));
	sprite.setPosition(position);
	if (bLoadRect)
		sprite.setTextureRect(rect);
	SetCenter();
	tID = id;
}

bool Object::changeTexture(std::string id)
{
	if (tID != id)
	{
		sprite.setTexture(Content::Instance().get(id), true);
		tID = id;
		return true;
	}
	return false;
}

void Object::SetMovement(float x, float y)
{
	if (x != 0)
		movement.x = x;
	if (y != 0)
		movement.y = y;
}

void Object::SetMovement(sf::Vector2f mMovement)
{
	movement = mMovement;
}

void Object::SetVelocity(float x, float y)
{
	if (x != 0)
		velocity.x = x;
	if (y != 0)
		velocity.y = y;
}

void Object::SetVelocity(sf::Vector2f mVelocity)
{
	velocity = mVelocity;
}

sf::Vector2f Object::GetVelocity()
{
	return velocity;
}

sf::Vector2f Object::GetMovement()
{
	return movement;
}


sf::Sprite Object::GetSprite()
{
	return sprite;
}

void Object::Animate(sf::Time deltaTime, int milliseconds, int width, int height)
{

	lastFrame += deltaTime;
	if(lastFrame.asMilliseconds() >= milliseconds)
	{
		if(width > 0)
		{
			if(rect.left < sprite.getTexture()->getSize().x - width)
			{
				rect.left += width;
				sprite.setTextureRect(rect);
			}
		}
		else if(width < 0)
		{
			if(rect.left > 0)
			{
				rect.left += width;
				sprite.setTextureRect(rect);
			}
		}
		lastFrame = lastFrame.Zero;
	}
}


void Object::SetDeadStatus(bool isDead) //set alive status
{
	bIsDead = isDead;
}

bool Object::GetDeadStatus()
{
	return bIsDead;
}

bool Object::WaitAnimation(int waitPoint)
{
	if (sprite.getTextureRect().left == waitPoint - sprite.getLocalBounds().width)
		return true;
	return false;
}

void Object::SetCenter()
{
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

bool Object::IsOffBounds()
{
	if (sprite.getPosition().x < 0)
		return true;
	if (sprite.getPosition().y < 0)
		return true;
	if (sprite.getPosition().x > 800)
		return true;
	if (sprite.getPosition().y > 600)
		return true;
	return false;
}

void Object::DamageObject(int hit)
{
	if (hit < 1)
		hit = 1;
	hitPoints -= hit;
	bIsHit = true;
	sprite.setColor(sf::Color(135,252,255,255));
}

int Object::GetHitPoints()
{
	return hitPoints;
}

void Object::SetMaxHitPoints(int hp)
{
	hitPoints = hp;
}

void Object::ExplodeObject(sf::Time deltaTime, float scale )
{
	if (changeTexture(explosionID))
	{
		if (sprite.getColor() != sf::Color::White)
			sprite.setColor(sf::Color::White);
		rect.top = 0;
		rect.left = 0;
		rect.width = 64;
		rect.height = 64;
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		SetCenter();
		sprite.scale(scale, scale);
		bIsExploding = true;
	}
	Object::Animate(deltaTime, 30, 64);
}

void Object::SetImmunity(float seconds)
{
	immunityTime = seconds;
	bIsImmune = true;
}

void Object::UpdateImmunity(sf::Time deltaTime, bool bIsFlashing)
{
	if (bIsImmune)
	{
		if (bIsFlashing)
		{
			immunityEffect += deltaTime;
			if (immunityEffect.asMilliseconds() >= 100)
			{
				sprite.setColor(sf::Color(255, 255, 255, 0));
				if (immunityEffect.asMilliseconds() >= 200)
					immunityEffect = immunityEffect.Zero;
			}
			else
				sprite.setColor(sf::Color::White);
		}
		immunityDelay += deltaTime;
		if (immunityDelay.asSeconds() > immunityTime)
		{
			bIsImmune = false;
			immunityDelay = immunityDelay.Zero;
			sprite.setColor(sf::Color::White);
			immunityEffect = immunityEffect.Zero;
		}
	}
}

bool Object::IsImmune()
{
	return bIsImmune;
}

Size Object::GetSize()
{
	return size;
}

void Object::setSize(Size size)
{
	this->size = size;
}

/*
ObjectTexture implementation
*/

void ObjectTexture::setTexture(int index, std::string id)
{
	std::vector<std::string>::iterator it = std::find(texturesID[index].begin(),texturesID[index].end(), id);
	if (it != texturesID[index].end())
		std::cout << "Texture with ID " << id << " is already registered!\n";
	else
		texturesID[index].push_back(id);
}

std::string ObjectTexture::getTexture(int index)
{
	return texturesID[index].back();
}