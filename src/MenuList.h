#ifndef MENULIST_H
#define MENULIST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

namespace Menu
{
	class MenuList
	{
	public:
		MenuList(sf::Vector2f position, int fontSize = 20, float spacing = 50.0f);
		MenuList(float x, float y, int fontSize = 20, float spacing = 50.0f);

		void AddNewOption(std::string text, sf::Font& font, std::function<void()> btnFunction);

		void MoveUp();
		void MoveDown();
		void MouseOver();

		void ExecuteButton();

		std::vector<Button> GetButtons();
	private:
		float _spacing;
		std::vector<Button> _buttons;
		sf::Vector2f _nextPos;
		int _curSelection;
		int _fontSize;
	};
}

#endif