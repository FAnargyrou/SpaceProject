/*				ContentManager.cpp
*				Created: 28/02/2015
*				Last Update: 04/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include <SFML\Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdint.h>

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

class ContentManager
{
public:
	//Singleton pattern
	static ContentManager& Instance();

	//Load a new texture (ID SHOULD BE PUT MANUALLY IN ID 'enum'!
	void load(std::string id, std::string fileName, bool bIsSmooth = false, bool bIsRepeated = false);

	//Returns texture (should be loaded first)
	sf::Texture& get(std::string id);
	const sf::Texture& get(std::string id) const;

private:
	ContentManager(){};
	std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
	static ContentManager* instance;
};

typedef ContentManager Content;