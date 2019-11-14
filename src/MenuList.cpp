#include "MenuList.h"

namespace Menu
{
	MenuList::MenuList(sf::Vector2f position, int fontSize, float spacing) :
		_position(position),
		_fontSize(fontSize),
		_spacing(spacing)
	{
		_curSelection = 0;
	}

	MenuList::MenuList(float x, float y, int fontSize, float spacing ) :
		_nextPos(sf::Vector2f(x, y)),
		_position(sf::Vector2f(x, y)),
		_fontSize(fontSize),
		_spacing(spacing)
	{
		_curSelection = 0;
	}

	void MenuList::AddNewOption(std::string text, sf::Font& font, std::function<void()> btnFunction)
	{
		_buttons.push_back(Button(font, text, btnFunction, _fontSize));
		_buttons.back().setOrigin(_buttons.back().getLocalBounds().width / 2, _buttons.back().getLocalBounds().height / 2);

		if (_buttons.size() == 1)
			_buttons.back().SetSelected(true);
		SetArea();
	}

	void MenuList::MoveUp()
	{
		_buttons[_curSelection].SetSelected(false);
		if (_curSelection == 0)
			_curSelection = _buttons.size() - 1;
		else
			_curSelection--;
		_buttons[_curSelection].SetSelected(true);

	}

	void MenuList::MoveDown()
	{
		_buttons[_curSelection].SetSelected(false);
		if (_curSelection == _buttons.size() - 1)
			_curSelection = 0;
		else
			_curSelection++;
		_buttons[_curSelection].SetSelected(true);
	}

	void MenuList::MouseOver()
	{

	}

	void MenuList::ExecuteButton()
	{
		_buttons[_curSelection].GetBtnFunction();
	}

	std::vector<Button> MenuList::GetButtons()
	{
		return _buttons;
	}

	void MenuList::SetArea()
	{
		sf::FloatRect totalArea;
		for (Button button : _buttons)
		{
			totalArea.height += button.getLocalBounds().height;
			if(totalArea.width < button.getLocalBounds().width)
				totalArea.width = button.getLocalBounds().width;
		}
		float spacingDiff = _spacing * _buttons.size() - 1;

		totalArea.height += spacingDiff;

		_nextPos.y = _position.y - totalArea.height / 4;
		_nextPos.x = _position.x;
		
		for (std::size_t index = 0; index < _buttons.size(); index++)
		{
			_buttons[index].setPosition(_nextPos.x, _nextPos.y);
			if(index + 1 < _buttons.size())
				if(_buttons[index + 1].IsSelected())
					_nextPos.y += _spacing;
			else
				_nextPos.y += _spacing;
		}
	}
}