#pragma once
#include <vector>
#include <map>
#include <string>
#include "ImageHandler.h"
using namespace std;

class Tile {
	sf::Texture texture;
	vector<sf::Sprite*> overlays;
	sf::Sprite sprite;
	vector<Tile*> neighbors;
	int position;
	int xBound, yBound;
	int isBomb;
	int numNeighbors;
	int neighborBombs;
	bool isFlagged, revealed;
	bool showNumber;
public:
	Tile();
	void SetTexture(string texture_);
	sf::Sprite GetSprite();
	void SetPosition(int i);
	void SetBounds(int x, int y);
	void SetFlag(bool flagged);
	void SetBomb(int i);
	void SetReveal(bool revealed);
	void SetNumber(bool showNumber);
	void ClearNeighbor();
	void SetNumberOverlay();
	void AddNeighbor(Tile* tileNeighbor, int position, int bomb);
	sf::Sprite* GetOverlay(int i);
	sf::Texture GetTexture();
	vector<Tile*> GetNeighbors();
	bool GetFlagged();
	bool GetRevealed();
	bool GetNumberShow();
	int GetPosition();
	int GetBomb();
	int GetNeighborBombs();
	int GetXBound();
	int GetYBound();
	~Tile();
};