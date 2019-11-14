#include "MainMenuState.h"

MainMenuState::MainMenuState(StateFactory& stateFactory, Settings settings) : 
	State(stateFactory, settings)
{

}

void MainMenuState::load()
{
	loader.LoadTextures("assets/textures.json");

	backgrounds.push_back(sf::Sprite(ContentManager::Instance().get("PurpleBackground")));
	backgrounds.push_back(sf::Sprite(ContentManager::Instance().get("DarkPurpleBackground")));
	backgrounds.push_back(sf::Sprite(ContentManager::Instance().get("BlueBackground")));
	backgrounds.push_back(sf::Sprite(ContentManager::Instance().get("BlackBackground")));

	background1 = backgrounds.begin();
	background2 = backgrounds.begin() + 1;
	for (sf::Sprite& bg : backgrounds)
		bg.setTextureRect(sf::IntRect(0, 0, SAFEAREA_W, SAFEAREA_H));

	sf::Vector2f size = GetSettings().GetWindow().getView().getSize();

	menuList.reset(new Menu::MenuList(size.x / 2, size.y / 2));

	std::function<void()> startGame = [this]() {
		this->StartGame();
	};

	std::function<void()> exitGame = [this]() {
		this->ExitGame();
	};

	menuList->AddNewOption("Start Game", GetSettings().GetFont(), startGame);
	menuList->AddNewOption("Settings", GetSettings().GetFont(), startGame);
	menuList->AddNewOption("exit to windows", GetSettings().GetFont(), exitGame);
}

void MainMenuState::clear()
{
	
}

bool MainMenuState::update(sf::Time deltaTime)
{
	sf::Time delay = sf::Time::Zero;

	UpdateBackgroundCycle(deltaTime, delay);

	return true;
}

void MainMenuState::render()
{
	sf::RenderWindow& window = GetSettings().GetWindow();

	window.draw(*background1);
	window.draw(*background2);

	for (Menu::Button button : menuList->GetButtons())
		window.draw(button);
}

bool MainMenuState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
			menuList->ExecuteButton();
		if (event.key.code == sf::Keyboard::Down)
			menuList->MoveDown();
		if (event.key.code == sf::Keyboard::Up)
			menuList->MoveUp();
	}

	return true;
}

void MainMenuState::StartGame()
{
	RequestPop();
	RequestPush(States::PLAY_STATE);
}

void MainMenuState::UpdateBackgroundCycle(sf::Time deltaTime, sf::Time& delay)
{
	if (delay > sf::Time::Zero)
		delay -= deltaTime;
	if (delay <= sf::Time::Zero)
	{
		if (bgAlpha < 255)
			bgAlpha++;
		background2->setColor(sf::Color(255, 255, 255, bgAlpha));
		if (bgAlpha >= 255)
		{
			background1->setColor(sf::Color(255, 255, 255, 0));
			background1++;
			if (background1 == backgrounds.end())
				background1 = backgrounds.begin();
			background2++;
			if (background2 == backgrounds.end())
				background2 = backgrounds.begin();
			background2->setColor(sf::Color(255, 255, 255, 0));
			bgAlpha = 0;
		}
	}
}

void MainMenuState::ExitGame()
{
	RequestClear();
}