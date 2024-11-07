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