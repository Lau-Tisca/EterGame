// Game.h

#pragma once

#include <string>
#include "GameBoard.h"
#include "Player.h"
#include "Wizard.h"
#include <vector>
#include "GameMode.h"
#include "ExplosionPattern.h"

class Game {
private:
    GameMode currentMode;
    GameBoard board;
    Player player1;
    Player player2;
    int currentPlayer; // 1 pentru player1, 2 pentru player2

    bool isWizardsDuel;

    void validateInput(int& row, int& col);
    void validateCardIndex(int& index, const Player& player);
    void checkForExplosion(int lastMoveRow, int lastMoveCol); // Noua metodă pentru verificarea exploziei

public:
    // Constructor
    Game(int boardSize,
        const std::string& player1Name,
        const std::string& player2Name,
        const Wizard& wizard1,
        const Wizard& wizard2,
        GameMode mode);

    // Constructor pentru Elements Duel
    Game(int boardSize,
        const std::string& player1Name,
        const std::string& player2Name,
        GameMode mode);

    // Metode
    void resetPlayerHand(Player& player);
    void resetGame();
    int validateRowInput(const std::string& prompt);
    std::pair<int, int> validateRowColInput(const std::string& prompt);
    bool useWizardAbility(Player& activePlayer, Player& opponent);
    bool useElementalPower(Player& user, Player& opponent);
    void start();
    void calculateFinalScore();
    bool placeIllusion(Player& activePlayer, GameBoard& board);
    bool placeNormalCard(Player& activePlayer, GameBoard& board, Player& opponent);

    // Getteri
    GameBoard& getBoard();
    Player& getPlayer1();
    Player& getPlayer2();
};
