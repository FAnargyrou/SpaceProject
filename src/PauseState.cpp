#include "PauseState.h"

PauseState::PauseState(StateFactory& stateFactory, Settings settings) : State(stateFactory, settings)
{
}

void PauseState::load()
{
	sf::Vector2f size = GetSettings().GetWindow().getView().getSize();

	background.setSize(size);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	pauseText.setFont(GetSettings().GetFont());
	pauseText.setString("PAUSE");
	pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
	pauseText.setPosition(size.x / 2, size.y / 2);
}

bool PauseState::update(sf::Time deltaTime)
{
	return false;
}

void PauseState::render()
{
	sf::RenderWindow& window = GetSettings().GetWindow();

	window.draw(background);
	window.draw(pauseText);
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			RequestPop();

	return false;
}