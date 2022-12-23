#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include "Tiles.h"
using namespace std;

//i used to have my own class here that did the same thing but longer, hence the file and class name difference

class TextureManager
{
	static map<string, sf::Texture> textures;
public:
	static void LoadTexture(string textureName);
	static sf::Texture& GetTexture(string textureName);
	static void Clear() { textures.clear(); }
};
