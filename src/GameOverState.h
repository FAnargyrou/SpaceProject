#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"
#include "MenuList.h"

class GameOverState : public State
{
public:
	GameOverState(StateFactory& stateFactory, Settings settings);

	void load() override;
	void clear() override;

	bool update(sf::Time deltaTime) override;
	void render() override;
	bool HandleEvent(const sf::Event& event) override;

	// Button functions
	void RestartGame();
	void ExitToMenu();

private:
	
	sf::Text gameOverText;
	sf::RectangleShape background;

	std::unique_ptr<Menu::MenuList> menuList;
};

#endif GAMEOVERSTATE_H