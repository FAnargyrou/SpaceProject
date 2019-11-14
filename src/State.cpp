#include "State.h"
#include "StateFactory.h"

State::Settings::Settings(sf::RenderWindow& window, sf::Font& font) :
	_window(&window),
	_font(&font)
{

}

sf::RenderWindow& State::Settings::GetWindow()
{
	return *_window;
}

sf::Font& State::Settings::GetFont()
{
	return *_font;
}

State::State(StateFactory& stateFactory, Settings settings) :
	_stateFactory(&stateFactory),
	_settings(settings)
{

}

void State::RequestPush(States state)
{
	_stateFactory->PushState(state);
}

void State::RequestPop()
{
	_stateFactory->PopState();
}

void State::RequestClear()
{
	_stateFactory->ClearStates();
}

State::Settings State::GetSettings() const
{
	return _settings;
}