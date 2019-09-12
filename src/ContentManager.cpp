/*				ContentManager.cpp
*				Created: 28/02/2015
*				Last Update: 01/03/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "ContentManager.h"



ContentManager* ContentManager::instance = nullptr;

ContentManager& ContentManager::Instance()
{
	if(instance == nullptr)
		instance = new ContentManager();
	return *instance;
}

void ContentManager::load(std::string id, std::string fileName, bool bIsSmooth, bool bIsRepeated)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if(!texture->loadFromFile(fileName))
		throw std::runtime_error("TextureHolder::load - Failed to load " + fileName);
	texture->setSmooth(bIsSmooth);
	texture->setRepeated(bIsRepeated);

	textureMap.insert(std::make_pair(id, std::move(texture)));
}


sf::Texture& ContentManager::get(std::string id)
{
	auto found = textureMap.find(id);
	return *found->second;
}

const sf::Texture& ContentManager::get(std::string id) const
{
	auto found = textureMap.find(id);
	return *found->second;
}