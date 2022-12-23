#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Tiles.h"
#include "ImageHandler.h"

class Board {
	sf::RenderWindow* window;
	int row;
	int col;
	int bombCount;
	int digitCount;
	vector<Tile*>board;
	int gameWin;
public:
	Board();
	void BoardInitialize(sf::RenderWindow* window);
	void BoardInitialize(string bombMap);
	void BoardDraw();
	void FlagDraw();
	void BombDraw();
	void NumberDraw();
	void FlagBombDraw();
	void ChangeBoardSize(int x, int y);
	void ClearNeighborTiles();
	void SetNeighborTiles();
	void SetDigitCount(int digitCount);
	void SetGameWin(int gameWin);
	void CheckGameWin();
	Tile* GetTile(int x, int y);
	void ClickTile(int x, int y);
	void FlagTile(int x, int y);
	sf::RenderWindow* GetWindow();
	vector <Tile*> GetTileBoard();
	bool BombCheck(int x, int y);
	bool FlagCheck(int x, int y);
	bool RevealCheck(int x, int y);
	int GetDigitCount();
	int GetGameWin();
	int GetCol();
	int GetRow();
	~Board();
};