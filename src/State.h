/*				GameState.h
*				Created: 08/04/2015
*				Last Update: 20/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#ifndef STATE_H
#define STATE_H
#include "ContentLoader.h"

enum States
{
	PLAY_STATE,
	PAUSE_STATE,
	MENU_STATE,
	BLANK_STATE
};

class StateFactory;

class State
{
public:

	struct Settings
	{
	public:

		Settings(sf::RenderWindow& window, sf::Font& font);
		sf::RenderWindow& GetWindow();
		sf::Font& GetFont();

	private:

		sf::RenderWindow* _window;
		sf::Font* _font;
	};

	State(StateFactory& stateFactory, Settings settings);
	typedef std::unique_ptr<State> StatePtr;

	virtual bool update(sf::Time deltaTime) = 0;
	virtual void render() = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

	virtual void load() = 0;
	virtual void clear() = 0;

protected:
	void RequestPush(States state);
	void RequestPop();
	void RequestClear();

	Settings GetSettings() const;
private:

	StateFactory* _stateFactory;

	Settings _settings;

};

#endif