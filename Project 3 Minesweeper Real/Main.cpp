#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "ImageHandler.h"
#include "Tiles.h"
#include "Board.h"
#include "BoardUi.h"
#include "Analyzer.h"

using namespace std;

void LoadAllTexture();

int main(){

    srand(time(NULL));
    LoadAllTexture();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    Board board;
    BoardUI boardUI;
    board.BoardInitialize(&window);
    boardUI.BoardUIInitialize(&window);


    Analyzer test = Analyzer(&window, 1000);

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        board.BoardDraw();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    //click on tile
                    if (pos.x < 800 && pos.y < 512 && board.GetGameWin() == 0) {
                        if (board.BombCheck(pos.x, pos.y) == false) {
                            if (board.FlagCheck(pos.x, pos.y) == false) {
                                board.ClickTile(pos.x, pos.y);
                            }
                        }
                        else if (board.FlagCheck(pos.x, pos.y) == false){
                            board.ClickTile(pos.x, pos.y);
                            board.SetGameWin(2);
                        }
                    }
                    //face fucntions
                    else if (pos.y >= 512 && pos.x < 400 && pos.x >= 336) {
                        boardUI.GetButtons().at(0)->SetTexture("face_happy");
                        board.BoardInitialize(boardUI.RandomGenerator());
                    }
                    //test functions
                    else if(pos.y >= 512 && pos.x < 748 && pos.x >= 556){
                        boardUI.GetButtons().at(0)->SetTexture("face_happy");
                        board.BoardInitialize(boardUI.ClickTest(pos.x, pos.y));
                    }
                    //debug fucntions
                    else if(pos.x >= 492 && pos.x < 556 && pos.y >= 512){
                        if (boardUI.GetToggle() == true) {
                            boardUI.SetToggle(false);
                        }
                        else {
                            boardUI.SetToggle(true);
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && board.GetGameWin() == 0) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    board.FlagTile(pos.x, pos.y);
                    if (board.FlagCheck(pos.x, pos.y) == true && board.RevealCheck(pos.x, pos.y) == false) {
                        board.SetDigitCount(board.GetDigitCount() - 1);
                    }
                    else if(board.FlagCheck(pos.x, pos.y) == false && board.RevealCheck(pos.x, pos.y) == false){
                        board.SetDigitCount(board.GetDigitCount() + 1);
                    }
                }
            }
            
        }
        board.CheckGameWin();
        board.NumberDraw();
        board.FlagDraw();
        if (boardUI.GetToggle() == true) {
            board.BombDraw();
        }
        if (board.GetGameWin() == 1) {
            boardUI.GetButtons().at(0)->SetTexture("face_win");
            board.FlagBombDraw();

        }
        else if (board.GetGameWin() == 2) {
            board.BombDraw();
            boardUI.GetButtons().at(0)->SetTexture("face_lose");
        }
        boardUI.BoardUIDraw();
        boardUI.CounterDraw(board.GetDigitCount());
        window.display();
    }
    window.clear();
    return 0;
}

void LoadAllTexture() {
    TextureManager::LoadTexture("debug");
    TextureManager::LoadTexture("digits");
    TextureManager::LoadTexture("face_happy");
    TextureManager::LoadTexture("face_lose");
    TextureManager::LoadTexture("face_win");
    TextureManager::LoadTexture("flag");
    TextureManager::LoadTexture("mine");
    TextureManager::LoadTexture("number_1");
    TextureManager::LoadTexture("number_2");
    TextureManager::LoadTexture("number_3");
    TextureManager::LoadTexture("number_4");
    TextureManager::LoadTexture("number_5");
    TextureManager::LoadTexture("number_6");
    TextureManager::LoadTexture("number_7");
    TextureManager::LoadTexture("number_8");
    TextureManager::LoadTexture("test_1");
    TextureManager::LoadTexture("test_2");
    TextureManager::LoadTexture("test_3");
    TextureManager::LoadTexture("tile_hidden");
    TextureManager::LoadTexture("tile_revealed");
}