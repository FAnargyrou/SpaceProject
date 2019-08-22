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

void ContentLoader::LoadContent(std::string filePath, ObjectTexture* objectTexture)
{
	LoadFile(filePath);
	Json::Value content = root["textures"];
	for (int array = 0; array < content.size(); array++)
	{
		std::string filePath = content[array].get("filePath", "NULL").asString();
		if (filePath != "NULL")
		{
			std::string id = content[array].get("textureID", NULL).asString();
			if (id == "NULL")
			{
				throw std::runtime_error("Texture ID cannot be NULL");
			}
			bool isSmooth = content[array].get("isSmooth", false).asBool();
			Content::Instance().load(id, filePath, isSmooth);
			int index = content[array].get("index", 1).asInt();
			objectTexture->setTexture(index, id);
		}
		else
			throw std::runtime_error("File Path from texture is NULL");
	}
	
}