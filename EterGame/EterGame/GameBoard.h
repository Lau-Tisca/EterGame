﻿#pragma once
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
#include "ExplosionPattern.h"

class GameBoard {
private:
    int size;
    /// board vechi
    /// std::vector<std::vector<std::optional<Card>>> board;

    /// board nou
    std::vector<std::vector<std::vector<std::optional<Card>>>> board;
    std::vector<std::pair<int, int>> holes; // Pozițiile "gropilor"
    //bool explosionOccurred;
    bool explosionOccurred = false;
	bool isFirstMove = true;

    Player* player1;
    Player* player2;

    //Metode
    bool isValidPosition(int row, int col, int depth) const;
    bool isEmptyPosition(int row, int col, int depth) const;
    bool checkLine(const Player& player, int startRow, int startCol, int dRow, int dCol) const;
    bool isLineFull(int startRow, int startCol, int dRow, int dCol) const;

public:
    // Constructor principal
    GameBoard(int size, Player& p1, Player& p2);
    // Secundar
    GameBoard(int size);

    bool isSpaceEmpty(int row, int col) const;

    void setFirstMove(bool value);

    //getter
    int getSize() const;

    //Metode
    void addHole(int row, int col);
    bool hasAdjacentCard(int row, int col) const;
    void createHole(int row, int col);
    bool isHole(int row, int col) const;

    bool placeCard(int row, int col, int depth, const Card& card, const Player& constPlayer);
    std::string checkWinCondition(const Player& player) const;

    void applyExplosion(const std::vector<std::pair<int, int>>& positions, int holeCount);

    bool triggerExplosion(Player& currentPlayer);


    void removeOpponentCardOverOwn(int row, int col, const Player& currentPlayer);
    void removeRowWithOwnCard(int row, const Player& currentPlayer);
    void coverOpponentCard(int row, int col, Player& currentPlayer);
    void moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void placeEtherCard(int row, int col, const Player& currentPlayer);
    void moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol);

    void controlledExplosion(Player& currentPlayer);
    void destruction(Player& opponent);
    void flames(Player& opponent, Player& currentPlayer);
    void lava(int number);
    void fromAshes(Player& currentPlayer, Card card);
    bool isCardCoveredByOpponent(int row, int col, int depth, const Player& player) const;
    Card removeTopCard(int row, int col);

    int calculateScore(const Player& player) const;
    bool checkIllusionRule(int row, int col, Player& opponent);
    void printBoard() const;
    std::vector<std::pair<int, int>> generateExplosionPattern();
};