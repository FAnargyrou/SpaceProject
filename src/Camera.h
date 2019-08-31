/*				Camera.h
*				Created: 03/03/2015
*				Last Update: 03/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/


#ifndef CAMERA_H
#define CAMERA_H
#include <SFML\Graphics.hpp>

class Camera : public sf::View
{
public:
	/*Move the camera
	velocity = which direction the camera is moving (in Vector2)
	*/
	void update(sf::Vector2f velocity);
};
#endif