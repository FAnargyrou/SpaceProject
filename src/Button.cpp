#include "Button.h"

namespace Menu
{
	Button::Button(sf::Font& font, std::string text, std::function<void()> btnFunction, int fontSize) :
		_isSelected(false)
	{
		setFont(font);
		setString(text);
		setCharacterSize(fontSize);
		setOutlineThickness(2);
		setOutlineColor(sf::Color::Black);
		_btnFunction = btnFunction;
	}

	void Button::SetSelected(bool isSelected)
	{
		if (_isSelected != isSelected)
		{
			if (isSelected)
			{
				setColor(sf::Color::Cyan);
				setCharacterSize(getCharacterSize() + 5);
			}
			else
			{
				setColor(sf::Color::White);
				setCharacterSize(getCharacterSize() - 5);
			}

			setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);

			_isSelected = isSelected;
		}

	}

	bool Button::IsSelected()
	{
		return _isSelected;
	}

	void Button::GetBtnFunction()
	{
		_btnFunction();
	}
}