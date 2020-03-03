/*				Game.cpp
*				Created: 28/02/2015
*				Last Update: 28/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "GameOverState.h"



Game::Game() : 
	_window(sf::VideoMode(1280, 720), "SFML" ), 
	timePerFrame(sf::seconds(1.f / 60.f)),
	stateFactory(State::Settings(_window, font))
{
	font.loadFromFile("assets/kenvector_future.ttf");

	RegisterStates();

	stateFactory.PushState(States::MENU_STATE);
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	_view.setSize(SAFEAREA_W, SAFEAREA_H);
	_view.setCenter(SAFEAREA_W/2, SAFEAREA_H/2);
	_view = GetLetterBoxView(_view, _window.getSize().x, _window.getSize().y);
	
	_window.setView(_view);

	ContentLoader contentLoad;
	


	while(_window.isOpen())
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
				_window.close();
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while(_window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::KeyPressed:
		case sf::Event::LostFocus:
			stateFactory.HandleEvent(event);
			break;
		case sf::Event::Resized:
			_view = GetLetterBoxView(_view, event.size.width, event.size.height);
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
	_window.setView(_view);
	_window.clear();
	stateFactory.render();
	_window.display();
}

void Game::RegisterStates()
{
	stateFactory.RegisterId<PlayState>(States::PLAY_STATE);
	stateFactory.RegisterId<GameOverState>(States::GAMEOVER_STATE);
	stateFactory.RegisterId<PauseState>(States::PAUSE_STATE);
	stateFactory.RegisterId<MainMenuState>(States::MENU_STATE);
}

sf::View Game::GetLetterBoxView(sf::View view, int windowWidth, int windowHeight)
{
	float windowRatio = windowWidth / (float) windowHeight;
	float viewRatio = view.getSize().x / view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.0f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.0f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return view;
}