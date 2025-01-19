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
#include <nlohmann/json.hpp>
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

    std::vector<std::vector<int>> boardState;
    //bool isEmptyPosition(int row, int col, int depth) const;
    //bool checkLine(const Player& player, int startRow, int startCol, int dRow, int dCol) const;

public:

    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& jsonData);
    // Constructor principal
    GameBoard(int size, Player& p1, Player& p2);
    // Constructor secundar
    GameBoard(int size);
    // getteri
    int getSize() const;
    // Setteri
    void setFirstMove(bool value);

    std::vector<Card> lastPlayedCards; // Reține ultimele cărți jucate
    std::pair<int, int> lastPlayedPosition; // Poziția ultimei mutări

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
    bool placeTCard(int row, int col, int depth, const Card& card, const Player& constPlayer);
    bool placeIllusion(int row, int col, Card card, Player& player);
    bool revealIllusion(int row, int col, int depth, Player& opponent);

    bool canTriggerExplosion() const;
    bool triggerExplosion(Player& currentPlayer);

    std::string checkWinCondition(const Player& player) const;

    //Afisare tabla
    void printBoard() const;

    void resetBoard();

    //Scor
    int calculateScore(const Player& player) const;

    bool hasAdjacentCard(int row, int col) const;
    bool checkIllusionRule(int row, int col, Player& opponent);

    // Puteri vrajitori
    bool removeOpponentCardOverOwn(int row, int col, const Player& currentPlayer);
    bool removeRowWithOwnCard(int row, const Player& currentPlayer);
    bool coverOpponentCard(int row, int col, Player& currentPlayer);
    bool moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    bool placeEtherCard(int row, int col, const Player& currentPlayer);
    bool moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer);
    bool moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol);

    // Abilități elementale
    bool applyDestruction(const Player& currentPlayer);
    bool applyFlames(const Player& currentPlayer);
    bool applyLava(const Player& currentPlayer);
    bool applyFromAshes(Player& currentPlayer);
    bool applySparks(Player& currentPlayer);
    bool applyBlizzard();
    bool applyWhirlwind();
    bool applyHurricane();
    bool applyBlast();
    bool applyMirage(Player& currentPlayer);
    bool applyStorm();
    bool applyTide();
    bool applyFog(Player& currentPlayer);
    bool applyWave();
    bool applyWhirlpool();
    bool applyTsunami();
    bool applyCascade();
    bool applySupport(Player& currentPlayer);
    bool applyEarthquake();
    bool applyShatter();
    bool applyBorders();
    bool applyAvalanche();
    bool applyBoulder();

    //Vadsad
};