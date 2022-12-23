#include <time.h>
#include <iostream>
#include "Tiles.h"
#include "ImageHandler.h"
#include "Board.h"
using namespace std;

Board::Board() {
	row = 16;
	col = 25;
}


void Board::BoardInitialize(sf::RenderWindow* window) {
	gameWin = 0;
	bombCount = 0;
	this->window = window;
	int count = 0;
	for (int i = 0; i < (row * col); i++) {
		board.push_back(new Tile);
		board.at(i)->SetBomb(0);
		board.at(i)->SetFlag(false);
		board.at(i)->SetPosition(i+1);
		board.at(i)->SetReveal(false);
	}
	//set bombs
	while (bombCount < 50) {
		int randomNumber = (rand() % 400);
		if (board.at(randomNumber)->GetBomb() != 1) {
			board.at(randomNumber)->SetBomb(1);
			bombCount++;
		}
	}
	//set overlays
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board.at(count)->SetBounds((32 * j), (32 * i));
			board.at(count)->GetOverlay(0)->move((32 * j), (32 * i));
			board.at(count)->GetOverlay(1)->move((32 * j), (32 * i));
			count++;
		}
	}
	//sets neighbor tiles
	ClearNeighborTiles();
	SetNeighborTiles();
	//sets number overlay if one
	count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetNeighborBombs() != 0) {
				board.at(count)->SetNumberOverlay();
				board.at(count)->GetOverlay(2)->move((32 * j), (32 * i));
			}
			count++;
		}
	}
	digitCount = bombCount;
}

void Board::BoardInitialize(string bombMap) {
	gameWin = 0;
	bombCount = 0;
	gameWin = false;
	this->window = window;
	board.clear();
	int count = 0;
	for (int i = 0; i < (row * col); i++) {
		board.push_back(new Tile);
		board.at(i)->SetFlag(false);
		board.at(i)->SetPosition(i+1);
		board.at(i)->SetReveal(false);
	}
	//set bombs
	for (int i = 0; i < (row*col); i++) {
			int temp = bombMap.at(i) - 48;
			if (bombMap.at(i) == '1') {
				bombCount++;
			}
			board.at(i)->SetBomb(temp);
	} 
	//set overlays
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board.at(count)->SetBounds((32 * j), (32 * i));
			board.at(count)->GetOverlay(0)->move((32 * j), (32 * i));
			board.at(count)->GetOverlay(1)->move((32 * j), (32 * i));
			count++;
		}
	}
	//sets neighbor tiles
	ClearNeighborTiles();
	SetNeighborTiles();
	for (int i = 0; i < board.size(); i++) {
	}
	//sets number overlay if one
	count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetNeighborBombs() != 0) {
				board.at(count)->SetNumberOverlay();
				board.at(count)->GetOverlay(2)->move((32 * j), (32 * i));
			}
			count++;
		}
	}
	digitCount = bombCount;
}

void Board::BoardDraw() {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			sf::Sprite spriteTemp = board.at(count)->GetSprite();
			spriteTemp.move((float)board.at(count)->GetXBound(), (float)board.at(count)->GetYBound());
			window->draw(spriteTemp);
			count++;
		}
	}
}

void Board::FlagDraw() {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetFlagged() == true) {
				sf::Sprite* spriteTemp = board.at(count)->GetOverlay(0);
				window->draw(*spriteTemp);
			}
			count++;
		}
	}
}

void Board::FlagBombDraw() {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetBomb() == 1) {
				sf::Sprite* spriteTemp = board.at(count)->GetOverlay(0);
				window->draw(*spriteTemp);
				if (digitCount > 0) {
					digitCount--;
				}
			}
			count++;
		}
	}
}

void Board::BombDraw() {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetBomb() >= 1) {
				sf::Sprite* spriteTemp = board.at(count)->GetOverlay(1);
				window->draw(*spriteTemp);
			}
			count++;
		}
	}
}

void Board::NumberDraw() {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board.at(count)->GetNeighborBombs() > 0 && board.at(count)->GetNumberShow() == true && board.at(count)->GetBomb() == 0) {
				sf::Sprite* spriteTemp = board.at(count)->GetOverlay(2);
				window->draw(*spriteTemp);
			}
			count++;
		}
	}
}

Tile* Board::GetTile(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound() + 32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetFlagged() == false) {
					return board.at(i);
				}
			}
		}
	}
}

void Board::ClickTile(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound()+32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetFlagged() == false) {
					board.at(i)->SetReveal(true);
					board.at(i)->SetTexture("tile_revealed");
					board.at(i)->SetNumber(true);
					for (int j = 0; j < board.at(i)->GetNeighbors().size(); j++) {
						if (board.at(i)->GetNeighborBombs() == 0 && board.at(i)->GetNeighbors().at(j)->GetRevealed() == false && board.at(i)->GetBomb() == 0) {
							ClickTile(board.at(i)->GetNeighbors().at(j)->GetXBound(), board.at(i)->GetNeighbors().at(j)->GetYBound());
						}
					}
				}
			}
		}
	}
}



void Board::FlagTile(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound() + 32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetRevealed() == false) {
					if (board.at(i)->GetFlagged() == true) {
						board.at(i)->SetFlag(false);
					}
					else {
						board.at(i)->SetFlag(true);
					}
				}
			}
		}
	}
}

void Board::CheckGameWin() {
	int check = 0;
	for (int i = 0; i < board.size(); i++) {
		if (board.at(i)->GetRevealed() == false && board.at(i)->GetBomb() == 0) {
			check--;
		}
		if (board.at(i)->GetRevealed() == false && board.at(i)->GetBomb() == 1) {
			check++;
		}
		if (check == bombCount && i == board.size() - 1) {
			gameWin = 1;
		}
	}
}

void Board::ChangeBoardSize(int x, int y) {
	row = x;
	col = y;
}

void Board::ClearNeighborTiles() {
	for (int i = 0; i < board.size(); i++) {
		board.at(i)->ClearNeighbor();
	}
}

void Board::SetNeighborTiles() {
	for (int i = 0; i < board.size(); i++) {
		if ((i - 26) >= 0 && (i - 26) % 25 != 24) {
			board.at(i)->AddNeighbor(board.at(i - 26), board.at(i - 26)->GetPosition(), board.at(i - 26)->GetBomb());
		}
		if ((i - 25) >= 0) {
			board.at(i)->AddNeighbor(board.at(i - 25), board.at(i - 25)->GetPosition(), board.at(i - 25)->GetBomb());
		}
		if ((i - 24) >= 0 && (i - 24) % 25 != 0) {
			board.at(i)->AddNeighbor(board.at(i - 24), board.at(i - 24)->GetPosition(), board.at(i - 24)->GetBomb());
		}
		if ((i - 1) >= 0 && (i - 1) % 25 != 24) {
			board.at(i)->AddNeighbor(board.at(i - 1), board.at(i - 1)->GetPosition(), board.at(i - 1)->GetBomb());
		}
		if ((i + 1) < board.size() && (i + 1) % 25 != 0) {
			board.at(i)->AddNeighbor(board.at(i + 1), board.at(i + 1)->GetPosition(), board.at(i + 1)->GetBomb());
		}
		if ((i + 24) < board.size() && (i + 24) % 25 != 24) {
			board.at(i)->AddNeighbor(board.at(i + 24), board.at(i + 24)->GetPosition(), board.at(i + 24)->GetBomb());
		}
		if ((i + 25) < board.size()) {
			board.at(i)->AddNeighbor(board.at(i + 25), board.at(i + 25)->GetPosition(), board.at(i + 25)->GetBomb());
		}
		if ((i + 26) < board.size() && (i + 26) % 25 != 0) {
			board.at(i)->AddNeighbor(board.at(i + 26), board.at(i + 26)->GetPosition(), board.at(i + 26)->GetBomb());
		}
	}
}

vector <Tile*> Board::GetTileBoard() {
	return board;
}

sf::RenderWindow* Board::GetWindow() {
	return window;
}

void Board::SetDigitCount(int digitCount) {
	this->digitCount = digitCount;
}

void Board::SetGameWin(int gameWin) {
	this->gameWin = gameWin;
}

int Board::GetGameWin() {
	return gameWin;
}

int Board::GetDigitCount() {
	return digitCount;
}

bool Board::BombCheck(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound() + 32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetRevealed() == false && board.at(i)->GetBomb() >= 1) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::FlagCheck(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound() + 32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetFlagged() == true) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::RevealCheck(int x, int y) {
	for (unsigned int i = 0; i < board.size(); i++) {
		if ((board.at(i)->GetXBound()) <= x && x < board.at(i)->GetXBound() + 32) {
			if ((board.at(i)->GetYBound()) <= y && y < board.at(i)->GetYBound() + 32) {
				if (board.at(i)->GetRevealed() == true) {
					return true;
				}
			}
		}
	}
	return false;
}

int Board::GetCol() {
	return col;
}

int Board::GetRow() {
	return row;
}

Board::~Board() {
}