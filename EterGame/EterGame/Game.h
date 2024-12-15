#pragma once
#include <string>
#include "GameBoard.h"
#include "Player.h"
#include "Wizard.h"

class Game {
private:
    GameBoard board;
    Player player1;
    Player player2;
    int currentPlayer; // 1 pentru player1, 2 pentru player2

    void validateInput(int& row, int& col);
    void validateCardIndex(int& index, const Player& player);
public:
    Game(int boardSize,
        const std::string& player1Name,
        const std::string& player2Name,
        const Wizard& wizard1,
        const Wizard& wizard2);

    void resetGame();
    void start();
    bool placeIllusion(Player& activePlayer, GameBoard& board);
    bool placeNormalCard(Player& activePlayer, GameBoard& board, Player& opponent);
};
