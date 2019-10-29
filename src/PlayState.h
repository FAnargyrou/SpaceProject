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
	void SpawnAsteroid(sf::Time deltaTime);

	void CollideObjects(Object* Object1, Object* Object2);
	sf::Time SpawnDelay;

	Player player;
	Enemy enemy;
	std::vector<Asteroid*> asteroids;

	sf::Sprite background;
	uint8 bgY;

	ObjectTexture asteroidTextures;
	ObjectTexture playerTextures;
	ObjectTexture enemyTextures;

	std::vector<ObjectData*> objectList;

	ContentLoader loader;
};
#endif