#pragma once
#include <iostream>
#include "Tiles.h"
#include "ImageHandler.h"
#include "Board.h"
#include "Buttons.h"

class BoardUI {
	sf::RenderWindow* window;
	vector<Button*> buttonList;
public:
	BoardUI();
	void BoardUIInitialize(sf::RenderWindow* window);
	void BoardUIDraw();
	void CounterDraw(int digitCount);
	void SetToggle(bool toggle);
	vector<Button*> GetButtons();
	string ClickTest(int x, int y);
	string RandomGenerator();
	bool GetToggle();
	~BoardUI();
};