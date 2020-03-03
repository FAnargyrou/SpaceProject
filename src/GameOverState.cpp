#include "GameOverState.h"

GameOverState::GameOverState(StateFactory& stateFactory, Settings settings) :
	State(stateFactory, settings)
{

}

void GameOverState::load()
{
	sf::Vector2f size = GetSettings().GetWindow().getView().getSize();

	background.setSize(size);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	gameOverText.setFont(GetSettings().GetFont());
	gameOverText.setOutlineThickness(2);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setString("PAUSE");
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
	gameOverText.setPosition(size.x / 2, size.y / 4);

	std::function<void()> exitFunction = [this]()
	{
		this->ExitToMenu();
	};

	std::function<void()> restartFunction = [this]()
	{
		this->RestartGame();
	};

	menuList.reset(new Menu::MenuList(size.x / 2, size.y / 2));

	menuList->AddNewOption("Restart", GetSettings().GetFont(), restartFunction);
	menuList->AddNewOption("Return to main menu", GetSettings().GetFont(), exitFunction);
}

void GameOverState::clear()
{

}

bool GameOverState::update(sf::Time deltaTime)
{
	return true;
}

void GameOverState::render()
{
	sf::RenderWindow& window = GetSettings().GetWindow();

	window.draw(background);
	window.draw(gameOverText);
	for (Menu::Button button : menuList->GetButtons())
	{
		window.draw(button);
	}
}

bool GameOverState::HandleEvent(const sf::Event& event)
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

void GameOverState::RestartGame()
{
	RequestClear();
	RequestPush(States::PLAY_STATE);
}

void GameOverState::ExitToMenu()
{
	RequestClear();
	RequestPush(States::MENU_STATE);
}