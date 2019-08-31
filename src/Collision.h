/*				Collision.h
*				Created: 02/03/2015
*				Last Update: 09/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/
#ifndef COLLISION_H
#define COLLISION_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>

//Get sprite size
sf::Vector2f GetSpriteSize(const sf::Sprite& Object);

//Get center of the sprite
sf::Vector2f GetSpriteCenter(const sf::Sprite& Object);

//Circular Collision Test
bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
#endif