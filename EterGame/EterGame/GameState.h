#pragma once

#include <vector>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct GameState {
    std::string gameMode;  // Modul de joc (Training, Mage Duel etc.)
    std::vector<std::vector<int>> board; // Starea tablei de joc
    std::vector<int> player1Hand; // Cărțile rămase ale Jucătorului 1
    std::vector<int> player2Hand; // Cărțile rămase ale Jucătorului 2
    int player1Score;
    int player2Score;

    // Convertire structura în JSON
    json to_json() const;

    // Creare structura din JSON
    static GameState from_json(const json& j);
};

// Funcții de salvare și încărcare
void saveGame(const GameState& gameState, const std::string& filename = "savegame.json");
GameState loadGame(const std::string& filename = "savegame.json");
