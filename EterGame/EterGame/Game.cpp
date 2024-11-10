#include <iostream>
#include "Game.h"
#include "Board.h"

void Game::startGame() {
	board.reset();

	for (auto& player : players) {
		player.resetDeck();
	}

	currentPlayer = 0;

	std::cout << "Game has started!\n";
}

void Game::checkWinCondition() {
    bool hasWinner = board.checkForWinner(); 

    if (hasWinner) {
        std::cout << "Jucătorul " << currentPlayer + 1 << " a câștigat!" << std::endl;
    }
    else {
        std::cout << "Jocul continuă!" << std::endl;
    }
}

void Game::nextTurn() {
	// Avansează la următorul jucător
	currentPlayer = (currentPlayer + 1) % players.size();

	// Afișează jucătorul curent
	std::cout << "It's the player's turn " << currentPlayer + 1 << std::endl;
}

void Game::saveGameState() {
    std::ofstream saveFile("game_state.txt");

    if (saveFile.is_open()) {
        // Salvează jucătorul curent
        saveFile << currentPlayer << std::endl;

        // Salvează starea fiecărui jucător
        for (const auto& player : players) {
            player.save(saveFile);  // Este necesar să ai o metodă save() în clasa Player
        }

        // Salvează starea tablei
        board.save(saveFile);  // Este necesar să ai o metodă save() în clasa Board

        saveFile.close();
        std::cout << "Starea jocului a fost salvată." << std::endl;
    }
    else {
        std::cerr << "Eroare la deschiderea fișierului pentru salvare!" << std::endl;
    }
}

void Game::loadGameState() {
    std::ifstream loadFile("game_state.txt");

    if (loadFile.is_open()) {

        loadFile >> currentPlayer;

        for (auto& player : players) {
            player.load(loadFile);  
        }

        board.load(loadFile); 

        loadFile.close();
        std::cout << "Starea jocului a fost încărcată." << std::endl;
    }
    else {
        std::cerr << "Eroare la deschiderea fișierului pentru încărcare!" << std::endl;
    }
}