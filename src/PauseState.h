#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"

class PauseState : public State
{
public:
	PauseState(StateFactory& stateFactory, Settings settings);

	void load() override;
	void clear() override {};

	bool update(sf::Time deltaTime) override;
	void render() override;
	bool HandleEvent(const sf::Event& event) override;

private:

	sf::RectangleShape background;
	sf::Text pauseText;
};

#endif
