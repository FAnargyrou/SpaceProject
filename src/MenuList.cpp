#include "MenuList.h"

namespace Menu
{
	MenuList::MenuList(sf::Vector2f position, int fontSize, float spacing) :
		_nextPos(position),
		_fontSize(fontSize),
		_spacing(spacing)
	{
		_curSelection = 0;
	}

	MenuList::MenuList(float x, float y, int fontSize, float spacing ) :
		_nextPos(sf::Vector2f(x, y)),
		_fontSize(fontSize),
		_spacing(spacing)
	{
		_curSelection = 0;
	}

	void MenuList::AddNewOption(std::string text, sf::Font& font, std::function<void()> btnFunction)
	{
		_buttons.push_back(Button(font, text, btnFunction, _fontSize));
		_buttons.back().setPosition(_nextPos);
		_nextPos.y += _spacing;

		if (_buttons.size() == 1)
			_buttons.back().SetSelected(true);
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
}