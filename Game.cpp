/*				Game.cpp
*				Created: 28/02/2015
*				Last Update: 28/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "SFML"), timePerFrame(sf::seconds(1.f / 60.f))
{
	
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	view.setSize(800, 600);
	view.setCenter(400, 300);

	ContentLoader contentLoad;
	Content::Instance().load("explosion", "assets/explosion2.png", true);

	play.load();

	while(window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
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
	play.update(deltaTime);
}

void Game::render()
{
	window.setView(view);
	window.clear();
	play.render(&window);
	window.display();
}

