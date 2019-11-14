/*				Object.h
*				Created: 28/02/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef OBJECT_H
#define OBJECT_H
#include "ContentManager.h"
#include "Collision.h"
#include <map>

enum Type
{
	ASTEROID = 0,
	PLAYER = 1,
	ENEMY = 2
};

struct ObjectData
{
public:
	ObjectData(std::string id, std::string textureId, std::string type, uint8 hitPoints, bool randomlySpawned, uint8 size, sf::Vector2f maxSpeed, std::string parentId);

	Type GetType();
	std::string GetParent();
	std::string GetId();
	std::string GetTextureId();
	uint8 GetHitPoints();
	uint8 GetSize();
	bool IsRandomlySpawned();
private:
	std::string _id;
	std::string _textureId;
	Type _type;
	sf::Vector2f _maxSpeed;
	uint8 _hitPoints;
	uint8 _size;
	bool _randomlySpawned;
	std::string _parentId;
};

class ObjectDataProcessor
{
public:
	//Singleton pattern
	static ObjectDataProcessor& Instance();

	ObjectData* FindObjectChild(const std::vector<ObjectData*> objectList, std::string name);
private:
	ObjectDataProcessor() {}
	static ObjectDataProcessor* instance;
};

//Base class for every enemy, missiles and pickups in the game (including player)
class Object
{
public:
	Object();

	//set bLoadRect to true if the object is using an animated sprite sheet
	virtual void load(ObjectData* objectData, sf::Vector2f position, bool bLoadRect = false);

	//Change texture; Return true if successful false if already changed
	bool changeTexture(std::string id);

	void SetMovement(float x, float y);
	void SetMovement(sf::Vector2f mMovement);

	void SetVelocity(float x, float y);
	void SetVelocity(sf::Vector2f mVelocity);

	//Returns object movement speed
	sf::Vector2f GetVelocity();
	sf::Vector2f GetMovement();

	//Returns object Sprite
	sf::Sprite GetSprite();

	//This function is for objects that needs to measure time to deal with it's logics
	virtual void update(sf::Time deltaTime);
	/*
	Function for sprite sheet animation
	deltaTime = time measuring and FPS pattern (Should come all the way from Game base class)
	milliseconds = how fast the animation flows
	width = width of each frame; used to move the animation to the left or to the right in your Sprite Sheet
	height = height of each frame; used to move the animation up or down in your Sprite Sheet (TO BE IMPLEMENTED)
	*/
	void Animate(sf::Time deltaTime, int milliseconds, int width, int height = 0);


	//Set if object is Dead or not
	void SetDeadStatus(bool isDead);
	bool GetDeadStatus();

	//Return true if animation was completed
	bool WaitAnimation(int waitPoint);

	//Return true if Object is outside window
	bool IsOffBounds();

	//Deals damage to the object
	void DamageObject(int hit = 1);
	//Gets object's current HP
	int GetHitPoints();

	void SetMaxHitPoints(int hp);
	void ExplodeObject(sf::Time deltaTime, float scale = 1.f);

	void SetImmunity(float seconds);
	void UpdateImmunity(sf::Time deltaTime, bool bIsFlashing = false);
	bool IsImmune();

	uint8 GetSize();
	void setSize(uint8 size);

	std::string GetObjectDataName();
protected:
	//Sets sprite origin relative to the current sprite
	void SetCenter();


	sf::Sprite sprite;
	sf::Vector2f velocity; //use velocity for speed increasing
	sf::Vector2f movement; //use movement for every move effect desired
	uint8 size;
	std::string tID;
	//Holds the ID for the explosion texture
	static std::string explosionID;

	std::string objectDataName;

	//This variable is for time measuring (To be used with update(sf::Time deltaTime))
	sf::Time lastFrame;
	sf::Time immunityDelay;
	sf::Time immunityEffect;
	float immunityTime;
	
	sf::IntRect rect;

	//Object states
	bool bIsHit;
	bool bIsDead;
	bool bIsExploding;
	bool bIsImmune;
	uint8 hitPoints;
};

struct ObjectTexture
{
public:
	void setTexture(uint16 index, std::string id);
	std::string getTexture(int index);
private:
	std::map<uint16, std::vector<std::string>> texturesID;
};


#endif