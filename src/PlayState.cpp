/*				PlayState.cpp
*				Created: 20/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "PlayState.h"

PlayState::PlayState(StateFactory& stateFactory, Settings settings) : State(stateFactory, settings)
{

}

void PlayState::load()
{
	loader.LoadTextures("assets/textures.json");
	loader.LoadObjectData("assets/ObjectData.json", objectList);
	ContentManager::Instance().load("explosion", "assets/explosion2.png", true);

	for (ObjectData* data : objectList)
		if (data->GetType() == Type::PLAYER)
			player.load(data, sf::Vector2f(SAFEAREA_W / 2, SAFEAREA_H));

	//TO DO: Remove hardcode for Background's texture; ID is currently defined in Textures.json but we have to manually match it here.
	background.setTexture(ContentManager::Instance().get("PurpleBackground"));
	background.setTextureRect(sf::IntRect(0, 0, SAFEAREA_W, SAFEAREA_H));

	std::srand((uint16)std::time(NULL));

	// Scoreboard system; For now hardcoded into a SF::Text format

	score = 0;
	scoreText.setFont(GetSettings().GetFont());
	scoreText.setString(std::to_string(score));
	scoreText.setColor(sf::Color::Cyan);
	scoreText.setOutlineThickness(1);
	scoreText.setOutlineColor(sf::Color::Black);

	scoreText.setPosition(50.f, 50.f);
}

void PlayState::clear()
{
	for (Asteroid* asteroid : asteroids)
		delete asteroid;
	asteroids.clear();
	ContentManager::Instance().ClearTextureMap();
}

bool PlayState::update(sf::Time deltaTime)
{
	if (bgY > -256)
		bgY--;
	else
		bgY = 0;
	background.setTextureRect(sf::IntRect(0, bgY, SAFEAREA_W, SAFEAREA_H));
	
	// Asteroids update loop
	Spawn(deltaTime);
	for (int astArray = 0; astArray < asteroids.size(); astArray++)
	{
		asteroids[astArray]->update(deltaTime);
		if (!asteroids[astArray]->GetDeadStatus())
		{
			for (int secondAstArray = 0; secondAstArray < asteroids.size(); secondAstArray++)
				if (secondAstArray != astArray)
					if (!asteroids[secondAstArray]->GetDeadStatus())
						if (CircleTest(asteroids[astArray]->GetSprite(), asteroids[secondAstArray]->GetSprite()) &&
							!asteroids[astArray]->IsImmune() && !asteroids[secondAstArray]->IsImmune())
							CollideObjects(asteroids[astArray], asteroids[secondAstArray]);

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
					UpdateScore(50);
				}

			}
			if (asteroids[astArray]->GetHitPoints() == 0)
				asteroids[astArray]->SetDeadStatus(true);
		}
		else
			DestroyAsteroid(astArray);

	}

	// Enemies update loop
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(deltaTime);
		if (CircleTest(player.GetSprite(), enemies[i]->GetSprite()))
		{
			if (!player.IsImmune())
			{
				enemies[i]->DamageObject();
				player.SetImmunity(2);
				//player.DamageObject();
			}
		}
		for (int m = 0; m < enemies[i]->GetMissiles().size(); m++)
		{
			if (CircleTest(enemies[i]->getMissileSprite(m), player.GetSprite()))
			{
				if (!player.IsImmune())
				{
					enemies[i]->DestroyMissile(m);
				}
			}
		}
		for (int m = 0; m < player.GetMissiles().size(); m++)
		{
			if (CircleTest(enemies[i]->GetSprite(), player.getMissileSprite(m)))
			{
				enemies[i]->DamageObject();
				player.DestroyMissile(m);
				UpdateScore(50);
			}

		}

		if (enemies[i]->GetDeadStatus())
		{
			if (enemies[i]->WaitAnimation(enemies[i]->GetSprite().getTexture()->getSize().x))
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}
	}

	player.update(deltaTime);

	return true;
}

void PlayState::render()
{
	sf::RenderWindow& window = GetSettings().GetWindow();

	window.draw(background);
	for (uint8 i = 0; i < player.GetMissiles().size(); i++)
		window.draw(player.getMissileSprite(i));
	for (uint8 astArray = 0; astArray < asteroids.size(); astArray++)
		window.draw(asteroids[astArray]->GetSprite());
	for (uint8 i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i]->GetSprite());
		for (uint8 m = 0; m < enemies[i]->GetMissiles().size(); m++)
			window.draw(enemies[i]->getMissileSprite(m));
	}
	window.draw(player.GetSprite());
	window.draw(scoreText);
}

bool PlayState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			RequestPush(States::PAUSE_STATE);
	if (event.type == sf::Event::LostFocus)
		RequestPush(States::PAUSE_STATE);
	return true;
}

void PlayState::DestroyAsteroid(int index)
{
	if (asteroids[index]->WaitAnimation(asteroids[index]->GetSprite().getTexture()->getSize().x / 2) && !asteroids[index]->IsDivided())
	{
		if (ObjectData* data = ObjectDataProcessor::Instance().FindObjectChild(objectList, asteroids[index]->GetObjectDataName()))
		{
			float velocity;
			for (int count = -1; count <= 1; count++)
			{
				velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
				if (Asteroid* asteroid = new Asteroid())
				{
					asteroid->load(data, asteroids[index]->GetSprite().getPosition());
					asteroid->SetDirection((float)count);
					asteroid->SetMovement(0, velocity);
					asteroid->SetImmunity(1.f);
					asteroids.push_back(asteroid);
				}
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

void PlayState::Spawn(sf::Time deltaTime)
{
	spawnDelay += deltaTime;
	if (spawnDelay.asSeconds() > 5)
	{
		int rand = std::rand() % 2;

		for (ObjectData* objectData : objectList)
		{
			if ((objectData->GetType() == Type::ASTEROID) && (rand == 0 || rand == 2))
				if (objectData->IsRandomlySpawned())
				{
					uint16 position = std::rand() % SAFEAREA_W - 15;
					float velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
					if (Asteroid* asteroid = new Asteroid())
					{
						asteroid->load(objectData, sf::Vector2f((float)position, -50));
						asteroid->SetMovement(0, velocity);
						asteroids.push_back(asteroid);
					}
				}
			if ((objectData->GetType() == Type::ENEMY) && (rand == 1 || rand == 2))
				if (objectData->IsRandomlySpawned())
				{
					uint16 position = std::rand() % SAFEAREA_W - 15;
					if (Enemy* enemy = new Enemy())
					{
						enemy->load(objectData, sf::Vector2f((float)position, -10));
						enemies.push_back(enemy);
					}
				}
			spawnDelay = spawnDelay.Zero;
		}

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

void PlayState::UpdateScore(uint8 points)
{
	score += points;
	scoreText.setString(std::to_string(score));
}