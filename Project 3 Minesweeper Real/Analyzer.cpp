#include "Analyzer.h"

using namespace std;

Analyzer::Analyzer() {
}

Analyzer::Analyzer(sf::RenderWindow* window, int n) {

	//create csv file to write to
	ofstream myFile;
	myFile.open("BombMap.csv");


	for (int i = 0; i < n; i++) {
		Board temp;
		temp.BoardInitialize(window);
		string tempString = getBoardString(&temp);
		myFile << tempString;
	}

	myFile.close();
}

Analyzer::~Analyzer() {

}

string Analyzer::getBoardString(Board *board) {
	vector<Tile*> boardTile = board->GetTileBoard();
	string toReturn;
	for (int i = 0; i < boardTile.size(); i++) {
		toReturn += to_string(boardTile[i]->GetBomb());
		toReturn += ",";
	}
	toReturn += "\n";
	return toReturn;
}