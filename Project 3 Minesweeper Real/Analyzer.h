#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tiles.h"
#include "Board.h"

class Analyzer {
	Board board;
public:
	Analyzer();
	Analyzer(sf::RenderWindow* window, int n);
	~Analyzer();
	string getBoardString(Board *board);
};