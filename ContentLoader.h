/*				Level.h
*				Created: 12/03/2015
*				Last Update: 07/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/


#ifndef CONTENTLOAD_H
#define CONTENTLOAD_H

#include <json\json.h>
#include <fstream>
#include "Player.h"
#include "GreyAsteroid.h"
#include "Enemy.h"


class ContentLoader
{
public:
	ContentLoader();
	void LoadContent(std::string filePath, ObjectTexture* objectTexture);
	void update(sf::Time deltaTime);
private:
	void LoadFile(std::string filePath);
	Json::Value root;
	Json::Reader reader;
	Json::Value content;
};
#endif