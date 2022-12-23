#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "Tiles.h"
#include "ImageHandler.h"
using namespace std;

map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName)
{
	string path = "images/";
	path += textureName + ".png";
	textures[textureName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	// Check to see if the texture already exists (i.e. has it been loaded yet?)
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}

