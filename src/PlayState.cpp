/*				PlayState.cpp
*				Created: 20/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "PlayState.h"

void PlayState::load()
{
	loader.LoadContent("assets/GreyAsteroid.json", &asteroidTextures);
	loader.LoadContent("assets/Player.json", &playerTextures);
	loader.LoadContent("assets/Enemy.json", &enemyTextures);

	player.load(playerTextures.getTexture(0), sf::Vector2f(400, 600));
	enemy.load(enemyTextures.getTexture(0), sf::Vector2f(40, 40));

	Content::Instance().load("background", "assets/purple.png", false, true);
	background.setTexture(Content::Instance().get("background"));
	background.setTextureRect(sf::IntRect(0, 0, 800, 600));

	std::srand((uint16)std::time(NULL));
}

void PlayState::clean()
{
	asteroids.clear();
}

void PlayState::update(sf::Time deltaTime)
{
	if (bgY > -256)
		bgY--;
	else
		bgY = 0;
	background.setTextureRect(sf::IntRect(0, bgY, 800, 600));
	SpawnAsteroid(deltaTime);
	for (int astArray = 0; astArray < asteroids.size(); astArray++)
	{
		asteroids[astArray]->update(deltaTime);
		if (!asteroids[astArray]->GetDeadStatus())
		{
			for (int secondAstArray = 0; secondAstArray < asteroids.size(); secondAstArray++)
			{
				if (secondAstArray != astArray)
				{
					if (!asteroids[secondAstArray]->GetDeadStatus())
					{
						if (CircleTest(asteroids[astArray]->GetSprite(), asteroids[secondAstArray]->GetSprite()) &&
							!asteroids[astArray]->IsImmune() && !asteroids[secondAstArray]->IsImmune())
						{
							CollideObjects(asteroids[astArray], asteroids[secondAstArray]);
						}
					}
				}
			 }
			if (CircleTest(player.GetSprite(), asteroids[astArray]->GetSprite()))
			{
				if (!player.IsImmune())
				{
					//player.damageObject();
					asteroids[astArray]->DamageObject();
					CollideObjects(&player, asteroids[astArray]);
				}
				if (player.GetHitPoints() == 0)
					player.SetDeadStatus(true);
				else
					player.SetImmunity(2);
				
			}
			for (int misArray = 0; misArray < player.GetMissiles().size(); misArray++)
			{
				if (CircleTest(asteroids[astArray]->GetSprite(), player.getMissileSprite(misArray)))
				{
					asteroids[astArray]->DamageObject();
					player.DestroyMissile(misArray);
				}

			}
			if (asteroids[astArray]->GetHitPoints() == 0)
				asteroids[astArray]->SetDeadStatus(true);
		}
		else
			DestroyAsteroid(astArray);

	}
	player.update(deltaTime);
	enemy.update(deltaTime);
}

void PlayState::render(sf::RenderWindow* window)
{
	window->draw(background);
	for (uint8 i = 0; i < player.GetMissiles().size(); i++)
		window->draw(player.getMissileSprite(i));
	for (uint8 astArray = 0; astArray < asteroids.size(); astArray++)
		window->draw(asteroids[astArray]->GetSprite());
	window->draw(player.GetSprite());
	window->draw(enemy.GetSprite());
	
}

void PlayState::DestroyAsteroid(int index)
{
	if (asteroids[index]->WaitAnimation(asteroids[index]->GetSprite().getTexture()->getSize().x / 2) && !asteroids[index]->IsDivided())
	{
		if (asteroids[index]->GetSize() == LARGE)
		{
			float velocity;
			for (int count = 1; count <= 3; count++)
			{
				velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
				asteroids.push_back(new GreyAsteroid());
				asteroids.back()->SetDirection<int>(count);
				asteroids.back()->setSize(MEDIUM);
				asteroids.back()->load(asteroidTextures.getTexture(1), asteroids[index]->GetSprite().getPosition());
				asteroids.back()->SetMaxHitPoints(3);
				asteroids.back()->SetMovement(0, velocity);
				asteroids.back()->SetImmunity(1.f);
			}
		}
		if (asteroids[index]->GetSize() == MEDIUM)
		{
			float velocity;
			for (int count = 1; count <= 3; count++)
			{
				velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
				asteroids.push_back(new GreyAsteroid());
				asteroids.back()->SetDirection<int>(count);
				asteroids.back()->setSize(SMALL);
				asteroids.back()->load(asteroidTextures.getTexture(2), asteroids[index]->GetSprite().getPosition());
				asteroids.back()->SetMaxHitPoints(1);
				asteroids.back()->SetMovement(0, velocity);
				asteroids.back()->SetImmunity(1.f);
			}
		}
		asteroids[index]->SetDivided(true);
	}
	if (asteroids[index]->WaitAnimation(asteroids[index]->GetSprite().getTexture()->getSize().x))
	{
		delete asteroids[index];
		asteroids.erase(asteroids.begin() + index);
	}


}

void PlayState::SpawnAsteroid(sf::Time deltaTime)
{
	SpawnDelay += deltaTime;
	if (SpawnDelay.asSeconds() > 3)
	{
		uint16 position = std::rand() % 785;
		float velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
		asteroids.push_back(new GreyAsteroid());
		asteroids.back()->load(asteroidTextures.getTexture(0), sf::Vector2f((float)position, -50));
		asteroids.back()->setSize(LARGE);
		asteroids.back()->SetMaxHitPoints(5);
		asteroids.back()->SetMovement(0, velocity);
		SpawnDelay = SpawnDelay.Zero;
	}
}

void PlayState::CollideObjects(Object* Object1, Object* Object2)
{
	sf::Vector2f movement1 = Object1->GetMovement();
	sf::Vector2f movement2 = Object2->GetMovement();

	sf::Vector2f result1, result2;

	int mass1 = Object1->GetSize() / 2;
	int mass2 = Object2->GetSize() / 2;

	result1.x = ((movement1.x * (mass1 - mass2) + (2 * mass2 * movement2.x)) / (mass1 + mass2));
	result1.y = ((movement1.y * (mass1 - mass2) + (2 * mass2 * movement2.y)) / (mass1 + mass2));

	

	result2.x = ((movement2.x * (mass2 - mass1) + (2 * mass1 * movement1.x)) / (mass1 + mass2));
	result2.y = ((movement2.y * (mass2 - mass1) + (2 * mass1 * movement1.y)) / (mass1 + mass2));

	Object1->SetMovement(result1);
	Object2->SetMovement(result2);
}