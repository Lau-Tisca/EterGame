#pragma once
#include <vector>
#include <optional>
#include <string>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib> // pentru rand()
#include <ctime>   // pentru srand()
#include "Card.h"
#include "Player.h"
#include <stack>
#include <vector>

class GameBoard {
private:
    int size;
    std::vector<std::vector<std::stack<Card>>> board;
    std::vector<std::pair<int, int>> holes; // Pozitiile „gropilor”

    bool isValidPosition(int row, int col) const;

public:
    GameBoard(int size);
    int getSize() const;

    void addHole(int row, int col);

    void createHole(int row, int col);
    bool isHole(int row, int col) const;

    bool placeCard(int row, int col, const Card card, const Player& currentPlayer);
    std::string checkWinCondition(const Player& player) const;

    void printBoard() const;

    bool triggerExplosion(Player& currentPlayer);

    
    void coverOpponentCard(int row, int col, Player& currentPlayer);
    void moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void placeEtherCard(int row, int col, const Player& currentPlayer);
    void moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol);

private:
    bool explosionOccurred = false; //Initializat ca false
    bool checkLine(const Player& player, int startRow, int startCol, int dRow, int dCol) const;
    bool isLineFull(int startRow, int startCol, int dRow, int dCol) const;
    std::vector<std::pair<int, int>> generateExplosionPattern();
};