#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <list>
#include "State.h"
#include "MenuList.h"

class PauseState : public State
{
public:
	PauseState(StateFactory& stateFactory, Settings settings);

	void load() override;
	void clear() override;

	bool update(sf::Time deltaTime) override;
	void render() override;
	bool HandleEvent(const sf::Event& event) override;


	// Button functions
	void ResumeGame();
	void ReturnToMenu();
private:

	sf::RectangleShape background;
	sf::Text pauseText;

	std::unique_ptr<Menu::MenuList> menuList;
};

#endif
