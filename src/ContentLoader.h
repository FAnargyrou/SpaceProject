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
#include <stdint.h>
#include <fstream>
#include "Player.h"
#include "GreyAsteroid.h"
#include "Enemy.h"

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

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