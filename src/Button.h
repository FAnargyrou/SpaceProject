#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "ContentLoader.h"
#include <functional>
#include <assert.h>

namespace Menu
{
	class Button : public sf::Text
	{
	public:
		Button(sf::Font& font, std::string text, std::function<void()> btnFunction, int fontSize = 20);

		

		void SetSelected(bool isSelected);

		void GetBtnFunction();

	private:
		bool _isSelected;
		std::function<void()> _btnFunction;
	};
}
#endif