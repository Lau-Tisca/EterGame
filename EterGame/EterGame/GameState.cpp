#include "GameState.h"
#include <iostream>
#include <fstream>

json GameState::to_json() const {
    return {
        {"gameMode", gameMode},
        {"board", board},
        {"player1Hand", player1Hand},
        {"player2Hand", player2Hand},
        {"player1Score", player1Score},
        {"player2Score", player2Score}
    };
}

GameState GameState::from_json(const json& j) {
    GameState state;
    j.at("gameMode").get_to(state.gameMode);
    j.at("board").get_to(state.board);
    j.at("player1Hand").get_to(state.player1Hand);
    j.at("player2Hand").get_to(state.player2Hand);
    j.at("player1Score").get_to(state.player1Score);
    j.at("player2Score").get_to(state.player2Score);
    return state;
}

void saveGame(const GameState& gameState, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << gameState.to_json().dump(4);  // Salvare JSON indentat
        file.close();
        std::cout << "✔ Progres salvat în " << filename << std::endl;
    }
    else {
        std::cerr << "❌ Eroare la salvarea jocului!" << std::endl;
    }
}

GameState loadGame(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();
        std::cout << "✔ Progres încărcat din " << filename << std::endl;
        return GameState::from_json(j);
    }
    else {
        std::cerr << "⚠ Nu s-a găsit fișierul de salvare! Se va începe un joc nou." << std::endl;
        return {}; // Returnează un GameState gol
    }
}
