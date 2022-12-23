#include <iostream>
#include "Tiles.h"
#include "ImageHandler.h"
#include "Board.h"
#include "BoardUi.h"
#include "Buttons.h"

BoardUI::BoardUI() {

}

void BoardUI::BoardUIInitialize(sf::RenderWindow* window) {
	this->window = window;

	buttonList.push_back(new Button("face_happy"));
	buttonList.at(0)->SetBounds(336, 512);
	buttonList.at(0)->SetPosition(1);

	buttonList.push_back(new Button("debug"));
	buttonList.at(1)->SetBounds(492, 512);
	buttonList.at(1)->SetPosition(2);

	buttonList.push_back(new Button("test_1"));
	buttonList.at(2)->SetBounds(556, 512);
	buttonList.at(2)->SetPosition(3);

	buttonList.push_back(new Button("test_2"));
	buttonList.at(3)->SetBounds(620, 512);
	buttonList.at(3)->SetPosition(4);

	buttonList.push_back(new Button("test_3"));
	buttonList.at(4)->SetBounds(684, 512);
	buttonList.at(4)->SetPosition(5);

	buttonList.push_back(new Button("digits"));
	buttonList.at(5)->SetBounds(0, 512);
	buttonList.at(5)->SetPosition(6);

	buttonList.push_back(new Button("digits"));
	buttonList.at(6)->SetBounds(21, 512);
	buttonList.at(6)->SetPosition(7);

	buttonList.push_back(new Button("digits"));
	buttonList.at(7)->SetBounds(42, 512);
	buttonList.at(7)->SetPosition(8);
}

void BoardUI::BoardUIDraw() {
	for (int i = 0; i < buttonList.size(); i++) {
		sf::Sprite spriteTemp = buttonList.at(i)->GetSprite();
		spriteTemp.move((float)buttonList.at(i)->GetXBound(), (float)buttonList.at(i)->GetYBound());
		window->draw(spriteTemp);
	}
}

void BoardUI::CounterDraw(int digitCount) {
	if (digitCount >= 0) {
		buttonList.at(5)->MoveTexture(sf::IntRect((digitCount / 100) * 21, 0, 21, 32));
		buttonList.at(6)->MoveTexture(sf::IntRect(((digitCount % 100) / 10) * 21, 0, 21, 32));
		buttonList.at(7)->MoveTexture(sf::IntRect(((digitCount % 100) % 10) * 21, 0, 21, 32));
	}
	else if (digitCount < 0) {
		buttonList.at(5)->MoveTexture(sf::IntRect(10 * 21, 0, 21, 32));
		buttonList.at(6)->MoveTexture(sf::IntRect((-1 * ((digitCount % 100) / 10) * 21), 0, 21, 32));
		buttonList.at(7)->MoveTexture(sf::IntRect((-1 * ((digitCount % 100) % 10) * 21), 0, 21, 32));
	}
}

vector<Button*> BoardUI::GetButtons() {
	return buttonList;
}

string BoardUI::ClickTest(int x, int y) {
	for (int i = 2; i < buttonList.size(); i++) {
		if ((buttonList.at(i)->GetXBound()) <= x && x < buttonList.at(i)->GetXBound() + 64) {
			if ((buttonList.at(i)->GetYBound()) <= y && y < buttonList.at(i)->GetYBound() + 64) {
				return buttonList.at(i)->TestFucntion(i + 1);
			}
		}
	}
}

string BoardUI::RandomGenerator() {
	int bombCount = 0;
	srand(time(NULL));
	// ._. theres other ways to get this but i thought it was interesting...
	string tempString = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	while (bombCount < 50) {
		int randomNumber = (rand() % 400);
		if (tempString.at(randomNumber) != '1') {
			tempString.at(randomNumber) = '1';
			bombCount++;
		}
	}
	return tempString;
}

void BoardUI::SetToggle(bool toggle) {
	buttonList.at(1)->SetToggle(toggle);
}

bool BoardUI::GetToggle() {
	return buttonList.at(1)->GetToggle();
}

BoardUI::~BoardUI() {

}