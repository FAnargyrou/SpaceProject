/*				Camera.cpp
*				Created: 03/03/2015
*				Last Update: 03/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Camera.h"

void Camera::update(sf::Vector2f velocity)
{
	move(velocity);
}