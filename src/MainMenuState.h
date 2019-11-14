#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "MenuList.h"

class MainMenuState : public State
{
public:
	MainMenuState(StateFactory& stateFactory, Settings settings);

	void load() override;
	void clear() override;

	bool update(sf::Time deltaTime) override;
	void render() override;
	bool HandleEvent(const sf::Event& event) override;

	void StartGame();
	void ExitGame();

private:
	void UpdateBackgroundCycle(sf::Time deltaTime, sf::Time& delay);

	std::vector<sf::Sprite> backgrounds;
	std::vector<sf::Sprite>::iterator background1;
	std::vector<sf::Sprite>::iterator background2;

	std::unique_ptr<Menu::MenuList> menuList;

	uint8 bgAlpha;

	ContentLoader loader;
	
};


#endif
