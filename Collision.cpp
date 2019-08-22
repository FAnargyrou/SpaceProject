/*				Collision.cpp
*				Created: 02/03/2015
*				Last Update: 09/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/


#include "Collision.h"

sf::Vector2f GetSpriteCenter (const sf::Sprite& Object)
{
	sf::FloatRect AABB = Object.getGlobalBounds();
	return sf::Vector2f (AABB.left+AABB.width/2.f, AABB.top+AABB.height/2.f);
}

sf::Vector2f GetSpriteSize (const sf::Sprite& Object)
{
	sf::IntRect OriginalSize = Object.getTextureRect();
	sf::Vector2f Scale = Object.getScale();
	return sf::Vector2f (OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
}

bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
{
	sf::Vector2f Obj1Size = GetSpriteSize(Object1);
	sf::Vector2f Obj2Size = GetSpriteSize(Object2);
	float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
	float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;
	sf::Vector2f Distance = GetSpriteCenter(Object1)-GetSpriteCenter(Object2);

	return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
}


