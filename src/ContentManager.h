/*				ContentManager.cpp
*				Created: 28/02/2015
*				Last Update: 04/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "Defines.h"

class ContentManager
{
public:
	//Singleton pattern
	static ContentManager& Instance();

	//Load a new texture (ID SHOULD BE PUT MANUALLY IN ID 'enum'!
	void load(std::string id, std::string fileName, bool bIsSmooth = false, bool bIsRepeated = false);

	//Clears texture list
	void ClearTextureMap();

	//Returns texture (should be loaded first)
	sf::Texture& get(std::string id);
	const sf::Texture& get(std::string id) const;

private:
	ContentManager(){};
	std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
	static ContentManager* instance;
};
