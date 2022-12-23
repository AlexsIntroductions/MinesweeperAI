#pragma once
#include "ImageHandler.h"

class Button {
	sf::Texture texture;
	sf::Sprite sprite;
	int position;
	int xBound, yBound;
	bool toggle;
public:
	Button();
	Button(string texture);
	void SetTexture(string texture);
	void MoveTexture(sf::IntRect rectangle);
	void SetPosition(int i);
	void SetBounds(int x, int y);
	void SetToggle(bool toggle);
	void Debug(Board* board);
	string TestFucntion(int position);
	void FaceFucntion();
	sf::Sprite GetSprite();
	sf::Texture GetTexture();
	bool GetToggle();
	int GetPosition();
	int GetXBound();
	int GetYBound();
	~Button();
};