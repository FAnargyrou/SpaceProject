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
#include "GameState.h"

class PlayState : public GameState
{
public:
	virtual void update(sf::Time deltaTime);
	virtual void render(sf::RenderWindow* window);

	virtual void load();
	virtual void clean();
private:
	void DestroyAsteroid(int index);
	void SpawnAsteroid(sf::Time deltaTime);

	void CollideObjects(Object* Object1, Object* Object2);
	sf::Time SpawnDelay;

	Player player;
	Enemy enemy;
	std::vector<Asteroid*> asteroids;

	sf::Sprite background;
	int bgY;

	ObjectTexture asteroidTextures;
	ObjectTexture playerTextures;
	ObjectTexture enemyTextures;

	ContentLoader loader;
};
#endif