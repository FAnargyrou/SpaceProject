/*				PlayState.h
*				Created: 20/04/2015
*				Last Update: 26/05/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include <ctime>
#include <random>
#include "State.h"

class PlayState : public State
{
public:
	PlayState(StateFactory& stateFactory, Settings settings);

	void load() override;
	void clear() override;
	bool HandleEvent(const sf::Event& event) override;

	bool update(sf::Time deltaTime) override;
	void render() override;
private:
	void DestroyAsteroid(int index);
	void Spawn(sf::Time deltaTime);

	void CollideObjects(Object* Object1, Object* Object2);

	void UpdateScore(uint8 points);

	sf::Time spawnDelay;

	Player player;
	std::vector<Enemy*> enemies;
	std::vector<Asteroid*> asteroids;

	sf::Sprite background;
	sf::Text scoreText;
	uint8 bgY;

	ObjectTexture asteroidTextures;
	ObjectTexture playerTextures;
	ObjectTexture enemyTextures;

	std::vector<ObjectData*> objectList;

	ContentLoader loader;

	uint32 score;

	bool isOver;
};
#endif