#pragma once
#include <vector>
#include <fstream>
#include "Board.h"
#include "Player.h"

class Game {
private:
	std::vector<Player> players;
	int currentPlayer;
	Board board;
public:
	Game(int linesAndCols) :
		board(linesAndCols),
		currentPlayer(0) {

	}

	~Game() {}

	void startGame();
	void nextTurn();
	void checkWinCondition();
	void saveGameState();
	void loadGameState();
};
