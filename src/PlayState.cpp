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

	for(ObjectData* data : objectList)
		if(data->GetType() == Type::PLAYER)
			player.load(data, sf::Vector2f(SAFEAREA_W / 2, SAFEAREA_H));

	ContentManager::Instance().load("background", "assets/purple.png", false, true);
	background.setTexture(ContentManager::Instance().get("background"));
	background.setTextureRect(sf::IntRect(0, 0, SAFEAREA_W, SAFEAREA_H));

	std::srand((uint16)std::time(NULL));
}

void PlayState::clear()
{
	for (Asteroid* asteroid : asteroids)
		delete asteroid;
	asteroids.clear();
}

bool PlayState::update(sf::Time deltaTime)
{
	if (bgY > -256)
		bgY--;
	else
		bgY = 0;
	background.setTextureRect(sf::IntRect(0, bgY, SAFEAREA_W, SAFEAREA_H));
	
	SpawnAsteroid(deltaTime);
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
	window.draw(player.GetSprite());
	window.draw(enemy.GetSprite());
	
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
			for (int count = 1; count <= 3; count++)
			{
				velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
				if (Asteroid* asteroid = new Asteroid())
				{
					asteroid->load(data, asteroids[index]->GetSprite().getPosition());
					asteroid->SetDirection<int>(count);
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

void PlayState::SpawnAsteroid(sf::Time deltaTime)
{
	SpawnDelay += deltaTime;
	if (SpawnDelay.asSeconds() > 3)
	{
		for (ObjectData* objectData : objectList)
			if (objectData->GetType() == Type::ASTEROID)
				if (objectData->IsRandomlySpawned())
				{
					uint16 position = std::rand() % SAFEAREA_W - 15;
					float velocity = ((float)std::rand() / (float)RAND_MAX * 1) + 1;
					if (Asteroid* asteroid = new Asteroid())
					{
						asteroid->load(objectData, sf::Vector2f((float)position, -50));
						asteroid->SetMovement(0, velocity);
						asteroids.push_back(asteroid);
						SpawnDelay = SpawnDelay.Zero;
						break;
					}
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