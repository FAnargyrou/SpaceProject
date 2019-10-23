/*				Game.cpp
*				Created: 28/02/2015
*				Last Update: 28/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Game.h"
#include "PlayState.h"

Game::Game() : window(sf::VideoMode(800, 600), "SFML"), timePerFrame(sf::seconds(1.f / 60.f))
{
	RegisterStates();

	stateFactory.PushState(States::PLAY_STATE);
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	view.setSize(800, 600);
	view.setCenter(400, 300);

	ContentLoader contentLoad;
	Content::Instance().load("explosion", "assets/explosion2.png", true);


	while(window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while(timeSinceLastUpdate > timePerFrame)
		{
			processEvents();
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			
			if (stateFactory.IsEmpty())
				window.close();
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	stateFactory.update(deltaTime);
}

void Game::render()
{
	window.setView(view);
	window.clear();
	stateFactory.render(&window);
	window.display();
}

void Game::RegisterStates()
{
	stateFactory.RegisterId<PlayState>(States::PLAY_STATE);
}