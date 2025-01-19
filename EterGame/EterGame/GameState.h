#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "Game.h"

class GameState {
public:
    Game game;  // Obiectul jocului care trebuie salvat/încărcat

    GameState() : game(3, "Player 1", "Player 2", GameMode::Training) {}

    // Funcții de salvare și încărcare
    void saveGame(const std::string& filename = "savegame.json") const;
    static GameState loadGame(const std::string& filename = "savegame.json");
};