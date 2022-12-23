#include <iostream>
#include <fstream>
#include "Board.h"
#include "Buttons.h"
#include "ImageHandler.h"

Button::Button() {
	toggle = false;
}

Button::Button(string texture_) {
	texture = TextureManager::GetTexture(texture_);
	sprite.setTexture(texture);
}

void Button::SetTexture(string texture_) {
	texture = TextureManager::GetTexture(texture_);
	sprite.setTexture(texture);
}

void Button::MoveTexture(sf::IntRect rectangle) {
	sprite.setTextureRect(rectangle);
}

void Button::SetPosition(int i) {
	position = i;
}

void Button::SetBounds(int x, int y) {
	xBound = x;
	yBound = y;
}

void Button::Debug(Board* board) {
	int count = 0;
	for (int i = 0; i < board->GetCol(); i++) {
		for (int j = 0; j < board->GetRow(); j++) {
			sf::Sprite spriteTemp = board->GetTileBoard().at(count)->GetSprite();
			spriteTemp.move((float)board->GetTileBoard().at(count)->GetXBound(), (float)board->GetTileBoard().at(count)->GetYBound());
			board->GetWindow()->draw(spriteTemp);
			count++;
		}
	}
}

string Button::TestFucntion(int position) {
	switch (position) {
	case 3: {
		ifstream fileName("boards/testboard1.brd");
		string bombMap = "";
		string tempString;
		while (getline(fileName, tempString)) {
			string substring = tempString.substr(0, tempString.size());
			bombMap = bombMap + substring;
		}
		return bombMap;
		break;
	}
	case 4: {
		ifstream fileName("boards/testboard2.brd");
		string bombMap = "";
		string tempString;
		while (getline(fileName, tempString)) {
			string substring = tempString.substr(0, tempString.size());
			bombMap = bombMap + substring;
		}
		return bombMap;
		break;
	}
	case 5: {
		ifstream fileName("boards/testboard3.brd");
		string bombMap = "";
		string tempString;
		while (getline(fileName, tempString)) {
			string substring = tempString.substr(0, tempString.size() );
			bombMap = bombMap + substring;
		}
		return bombMap;
		break;
	}
	default:
		cout << "Im stunned on how this triggered in Buttons.TestFucntion()'s code." << endl;
		break;
	}
}

void Button::SetToggle(bool toggle) {
	this->toggle = toggle;
}

sf::Sprite Button::GetSprite() {
	return sprite;
}

sf::Texture Button::GetTexture() {
	return texture;
}

bool Button::GetToggle() {
	return toggle;
}

int Button::GetPosition() {
	return position;
}

int Button::GetXBound() {
	return xBound;
}

int Button::GetYBound() {
	return yBound;
}

Button::~Button() {

}