#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
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

    int currentRound;

    bool isWizardsDuel;
    bool isElementalDuel;
    bool isTournamentMode;

    std::vector<std::vector<int>> battleArena;

    int player1Markers;
    int player2Markers;

    void validateInput(int& row, int& col);
    void validateCardIndex(int& index, const Player& player);
    void checkForExplosion(int lastMoveRow, int lastMoveCol); // Noua metodă pentru verificarea exploziei

    void placeMarker(int row, int col, int player); // Plasare marker în Battle Arena
    bool checkTournamentWin(int player); // Verifică victoria în turneu
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

    // Funcții de serializare
    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& jsonData);

    void startGame();
    void saveGameState(const std::string& filename = "savegame.json") const;
    //void saveGameState(const std::string& filename = "C:/Users/Public/savegame.json") const;
    bool loadGameState(const std::string& filename = "savegame.json");
    //bool loadGameState(const std::string& filename = "C:/Users/Public/savegame.json");

    // Metode
    void startTournament();
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
