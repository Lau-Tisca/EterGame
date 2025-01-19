#include "GameState.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void GameState::saveGame(const std::string& filename) const {
    std::cout << "[DEBUG] Saving game to " << filename << "...\n";

    json saveData;
    saveData["game"] = game.toJson();  // Serializăm obiectul jocului

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] Failed to open save file!\n";
        return;
    }

    file << saveData.dump(4);
    file.close();
    std::cout << "[DEBUG] Game saved successfully!\n";
}

GameState GameState::loadGame(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] No saved game found!\n";
        return GameState(); // Returnează un joc nou dacă nu există salvare
    }

    json saveData;
    try {
        file >> saveData;
        file.close();
    }
    catch (...) {
        std::cerr << "[ERROR] Failed to parse savegame.json. Starting a new game.\n";
        return GameState();
    }

    std::cout << "[DEBUG] Loaded JSON: " << saveData.dump(4) << "\n";

    GameState gameState;
    gameState.game.fromJson(saveData["game"]);

    std::cout << "[DEBUG] Game loaded successfully!\n";
    return gameState;
}

