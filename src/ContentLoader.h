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
#include "Asteroid.h"
#include "Enemy.h"


class ContentLoader
{
public:
	ContentLoader();
	void LoadTextures(std::string filePath);
	void LoadObjectData(std::string filePath, std::vector<ObjectData*>& objectList);
private:
	void LoadFile(std::string filePath);
	Json::Value root;
	Json::Reader reader;
	Json::Value content;
};
#endif