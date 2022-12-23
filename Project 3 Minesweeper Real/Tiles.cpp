#include "Tiles.h"
#include "ImageHandler.h"


Tile::Tile() {
	texture = TextureManager::GetTexture("tile_hidden");
	sprite.setTexture(texture);
	isFlagged = false;
	showNumber = false;
	numNeighbors = 0;
	overlays.push_back(new sf::Sprite);
	overlays.at(0)->setTexture(TextureManager::GetTexture("flag"));
	overlays.push_back(new sf::Sprite);
	overlays.at(1)->setTexture(TextureManager::GetTexture("mine"));
}

Tile::~Tile() {

}

void Tile::SetTexture(string texture_) {
	texture = TextureManager::GetTexture(texture_);
	sprite.setTexture(texture);
}

void Tile::SetReveal(bool revealed_) {
	revealed = revealed_;
}

sf::Sprite Tile::GetSprite() {
	return sprite;
}

void Tile::SetPosition(int i) {
	position = i;
}

void Tile::SetBomb(int i) {
	isBomb = i;
}

void Tile::SetBounds(int x, int y) {
	xBound = x;
	yBound = y;
}

void Tile::SetFlag(bool flagged) {
	isFlagged = flagged;
}

void Tile::SetNumber(bool showNumber) {
	this->showNumber = true;
}

void Tile::ClearNeighbor() {
	neighbors.clear();
}

void Tile::SetNumberOverlay() {
	string fileName = "number_";
	fileName = fileName + to_string(neighborBombs);
	overlays.push_back(new sf::Sprite);
	overlays.at(2)->setTexture(TextureManager::GetTexture(fileName));
}

void Tile::AddNeighbor(Tile* tileNeighbor, int position, int bomb) {
	neighbors.push_back(tileNeighbor);
	if (tileNeighbor->GetBomb() == 1) {
		neighborBombs += 1;
	}
	numNeighbors += 1;
}

sf::Sprite* Tile::GetOverlay(int i) {
	return overlays.at(i);
}

sf::Texture Tile::GetTexture() {
	return texture;
}

vector<Tile*> Tile::GetNeighbors() {
	return neighbors;
}

bool Tile::GetRevealed() {
	return revealed;
}

bool Tile::GetFlagged() {
	return isFlagged;
}

bool Tile::GetNumberShow() {
	return showNumber;
}

int Tile::GetPosition() {
	return position;
}

int Tile::GetBomb() {
	return isBomb;
}

int Tile::GetNeighborBombs() {
	return neighborBombs;
}

int Tile::GetXBound() {
	return xBound;
}

int Tile::GetYBound() {
	return yBound;
}