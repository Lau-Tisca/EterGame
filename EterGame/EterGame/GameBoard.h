//GameBoard.h

#pragma once

#include <vector>
#include <optional>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cstdlib> // pentru rand()
#include <ctime>   // pentru srand()
#include "Card.h"
#include "Player.h"
#include "ExplosionPattern.h"

class ExplosionPattern;

class GameBoard {
private:
    int size;
    std::vector<std::vector<std::vector<std::optional<Card>>>> board;
    std::vector<std::pair<int, int>> holes; // Pozițiile "gropilor"
    bool explosionOccurred = false;
    bool isFirstMove = true;

    //Pointeri la playeri
    Player* player1;
    Player* player2;

    //Metode
    bool isLineFull(int startRow, int startCol, int dRow, int dCol) const;
    void applyExplosion(const ExplosionPattern& explosion);

    void validateBoardIntegrity();


    //bool isEmptyPosition(int row, int col, int depth) const;
    //bool checkLine(const Player& player, int startRow, int startCol, int dRow, int dCol) const;

public:
    // Constructor principal
    GameBoard(int size, Player& p1, Player& p2);
    // Constructor secundar
    GameBoard(int size);
    // getteri
    int getSize() const;
    // Setteri
    void setFirstMove(bool value);

    /// METODE
    bool isValidPosition(int row, int col, int depth) const;
    // Verificare daca exista gaura
    bool isHole(int row, int col) const;

    bool isSpaceEmpty(int row, int col) const;

    bool isCardConnected(int row, int col) const;

    bool isOccupiedBy(const Player& player, int row, int col) const;
    // Crearea groapa
    bool createHole(int row, int col);

    // Eliminare card
    void removeCard(int x, int y);

    // Returnare la player
    void returnCardToPlayer(int x, int y);

    bool placeCard(int row, int col, int depth, const Card& card, const Player& constPlayer);

    bool placeIllusion(int row, int col, Card card, Player& player);
    bool revealIllusion(int row, int col, int depth, Player& opponent);

    bool canTriggerExplosion() const;
    bool triggerExplosion(Player& currentPlayer);

    std::string checkWinCondition(const Player& player) const;

    //Afisare tabla
    void printBoard() const;

    //Scor
    int calculateScore(const Player& player) const;

    bool hasAdjacentCard(int row, int col) const;
    bool checkIllusionRule(int row, int col, Player& opponent);




    // eliminat momentan bool isSpaceEmpty(int row, int col) const;

    // eliminat momentan void addHole(int row, int col);

    // eliminat momentan void removeHole(int row, int col);

    // eliminat momentan bool isBoardStillConnected();

    // Puteri vrajitori
    void removeOpponentCardOverOwn(int row, int col, const Player& currentPlayer);
    void removeRowWithOwnCard(int row, const Player& currentPlayer);
    void coverOpponentCard(int row, int col, Player& currentPlayer);
    void moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void placeEtherCard(int row, int col, const Player& currentPlayer);
    void moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    void moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol);

    // Puteri elemente
    /*  TO DO: sa modific metodele de mai jos pentru a se potrivi cu board-ul nou
    void controlledExplosion(Player& currentPlayer);
    void destruction(Player& opponent);
    void flames(Player& opponent, Player& currentPlayer);
    void lava(int number);
    void fromAshes(Player& currentPlayer, Card card);
    bool isCardCoveredByOpponent(int row, int col, int depth, const Player& player) const;
    Card removeTopCard(int row, int col);
    bool moveCoveredCard(const Player& player, int sourceRow, int sourceCol, int targetRow, int targetCol);
    */

    //Vadsad
};