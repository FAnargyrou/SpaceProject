/*				ContentLoader.h
*				Created: 12/03/2015
*				Last Update: 07/04/2015
*
*				Created by: Felipe Anargyrou
*				E-Mail : anargyrou4@hotmail.com
*/

#include "ContentLoader.h"

ContentLoader::ContentLoader()
{
}

void ContentLoader::LoadFile(std::string filePath)
{
	std::ifstream file(filePath);
	if (!reader.parse(file, root))
	{
		throw std::runtime_error(" Failed to load " + reader.getFormattedErrorMessages());
		return;
	}
}

void ContentLoader::LoadTextures(std::string filePath)
{
	LoadFile(filePath);
	Json::Value content = root["textures"];
	for (uint16 array = 0; array < content.size(); array++)
	{
		std::string filePath = content[array].get("filePath", "NULL").asString();
		if (filePath != "NULL")
		{
			std::string id = content[array].get("textureID", "NULL").asString();
			if (id == "NULL")
			{
				throw std::runtime_error("Object name cannot be NULL");
			}
			bool isSmooth = content[array].get("isSmooth", false).asBool();
			bool isRepeated = content[array].get("isRepeated", false).asBool();
			ContentManager::Instance().load(id, filePath, isSmooth, isRepeated);
		}
		else
			throw std::runtime_error("File Path from texture is NULL");
	}
	
}

void ContentLoader::LoadObjectData(std::string filePath, std::vector<ObjectData*>& objectList)
{
	LoadFile(filePath);

	Json::Value content = root["data"];

	for (uint16 array = 0; array < content.size(); array++)
	{
		std::string type = content[array].get("type", "NULL").asString();
		if (type != "NULL" && type != "Player" && type != "Enemy" && type != "Asteroid")
			std::runtime_error("Object Type is either invalid or is missing");
		else
		{
			std::string name = content[array].get("name", "NULL").asString();
			std::string textureId = content[array].get("textureId", "NULL").asString();
			if (name != "NULL" && textureId != "NULL")
			{
				uint8 hitPoints = content[array].get("hitPoints", 1).asUInt();
				sf::Vector2f maxSpeed(content[array].get("maxVelocityX", 0.0f).asFloat(), content[array].get("maxVelocityY", 0.0f).asFloat());
				uint8 size = content[array].get("size", 1).asUInt();
				bool randomSpawn = content[array].get("RandomSpawn", false).asBool();
				std::string parentId = content[array].get("parent", "NULL").asString();

				objectList.push_back(new ObjectData(name, textureId, type, hitPoints, randomSpawn, size, maxSpeed, parentId));
			}
			else
				std::runtime_error("Object Name is NULL. Please make sure you're specifying a name for all Objects.");
		}
	}
}