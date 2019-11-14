#include "PauseState.h"

PauseState::PauseState(StateFactory& stateFactory, Settings settings) : 
	State(stateFactory, settings)
{
}

void PauseState::load()
{
	sf::Vector2f size = GetSettings().GetWindow().getView().getSize();

	background.setSize(size);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	pauseText.setFont(GetSettings().GetFont());
	pauseText.setOutlineThickness(2);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setString("PAUSE");
	pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
	pauseText.setPosition(size.x / 2, size.y / 4);

	std::function<void()> exitFunction = [this]()
	{
		this->ReturnToMenu();
	};

	std::function<void()> resumeFunction = [this]()
	{
		this->ResumeGame();
	};

	menuList.reset(new Menu::MenuList(size.x / 2, size.y / 2));

	menuList->AddNewOption("Resume", GetSettings().GetFont(), resumeFunction);
	menuList->AddNewOption("Return to main menu", GetSettings().GetFont(), exitFunction);

}

void PauseState::clear()
{
	
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
	for (Menu::Button button : menuList->GetButtons())
	{
		window.draw(button);
	}
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			RequestPop();
		if (event.key.code == sf::Keyboard::Enter)
			menuList->ExecuteButton();
		if (event.key.code == sf::Keyboard::Down)
			menuList->MoveDown();
		if (event.key.code == sf::Keyboard::Up)
			menuList->MoveUp();
	}

	return false;
}

void PauseState::ResumeGame()
{
	RequestPop();
}

void PauseState::ReturnToMenu()
{
	RequestClear();
	RequestPush(States::MENU_STATE);
}