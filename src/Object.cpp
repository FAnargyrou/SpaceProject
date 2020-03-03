/*				Object.cpp
*				Created: 28/02/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Object.h"

ObjectData::ObjectData(std::string id, std::string textureId, std::string type, uint8 hitPoints, bool randomlySpawned, uint8 size, sf::Vector2f maxSpeed, std::string parentId)
	: _id(id), _textureId(textureId), _hitPoints(hitPoints), _randomlySpawned(randomlySpawned), _size(size), _maxSpeed(maxSpeed)
{
	if (parentId != "NULL" && parentId != _id)
		_parentId = parentId;
	if (type == "Asteroid")
		_type = ASTEROID;
	else if (type == "Player")
		_type = PLAYER;
	else if (type == "Enemy")
		_type = ENEMY;
}

Type ObjectData::GetType()
{
	return _type;
}

std::string ObjectData::GetParent()
{
	return _parentId;
}

std::string ObjectData::GetId()
{
	return _id;
}

std::string ObjectData::GetTextureId()
{
	return _textureId;
}

uint8 ObjectData::GetHitPoints()
{
	return _hitPoints;
}

uint8 ObjectData::GetSize()
{
	return _size;
}

bool ObjectData::IsRandomlySpawned()
{
	return _randomlySpawned;
}



ObjectDataProcessor* ObjectDataProcessor::instance = nullptr;

ObjectDataProcessor& ObjectDataProcessor::Instance()
{
	if (instance == nullptr)
		instance = new ObjectDataProcessor();
	return *instance;
}

ObjectData* ObjectDataProcessor::FindObjectChild(const std::vector<ObjectData*> objectList, std::string name)
{
	for (ObjectData* data : objectList)
		if (data->GetParent() == name)
			return data;
	return nullptr;
}


std::string Object::explosionID = "explosion";

Object::Object()
{
	bIsDead = false;
	bIsExploding = false;
	bIsHit = false;
	bIsImmune = false;
}

//Before definition
void Object::load(ObjectData* objectData, sf::Vector2f position, bool bLoadRect)
{
	std::string id = objectData->GetTextureId();
	sprite.setTexture(ContentManager::Instance().get(id));

	SetMaxHitPoints(objectData->GetHitPoints());
	size = objectData->GetSize();

	objectDataName = objectData->GetId();
	
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
		sprite.setTexture(ContentManager::Instance().get(id), true);
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

void Object::update(sf::Time deltaTime)
{
	if (sprite.getPosition().x < 0 - sprite.getLocalBounds().width)
		sprite.setPosition(SAFEAREA_W + sprite.getLocalBounds().width / 2, sprite.getPosition().y);
	if (sprite.getPosition().y < 0 - sprite.getLocalBounds().height)
		sprite.setPosition(sprite.getPosition().x, SAFEAREA_H + sprite.getLocalBounds().height / 2);
	if (sprite.getPosition().x > SAFEAREA_W + sprite.getLocalBounds().width)
		sprite.setPosition(0 - sprite.getLocalBounds().width / 2, sprite.getPosition().y);
	if (sprite.getPosition().y > SAFEAREA_H + sprite.getLocalBounds().height)
		sprite.setPosition(sprite.getPosition().x, 0 - sprite.getLocalBounds().height / 2);
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
	if (sprite.getPosition().x < 0 - sprite.getLocalBounds().width)
		return true;
	if (sprite.getPosition().y < 0 - sprite.getLocalBounds().height)
		return true;
	if (sprite.getPosition().x > SAFEAREA_W + sprite.getLocalBounds().width)
		return true;
	if (sprite.getPosition().y > SAFEAREA_H + sprite.getLocalBounds().height)
		return true;
	return false;
}

void Object::DamageObject(int hit, bool setImmunity)
{
	if (setImmunity)
		SetImmunity(2.0f);
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

uint8 Object::GetSize()
{
	return size;
}

void Object::setSize(uint8 size)
{
	this->size = size;
}

std::string Object::GetObjectDataName()
{
	return objectDataName;
}

/*
ObjectTexture implementation
*/

void ObjectTexture::setTexture(uint16 index, std::string id)
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

