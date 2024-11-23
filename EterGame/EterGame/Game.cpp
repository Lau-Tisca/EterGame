#include <iostream>
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"

Game::Game(int boardSize, const std::string& player1Name, const std::string& player2Name,
    const Wizard& wizard1, const Wizard& wizard2)
    : board(boardSize),
    player1(player1Name, wizard1), // Asociază vrăjitorul 1 jucătorului 1
    player2(player2Name, wizard2), // Asociază vrăjitorul 2 jucătorului 2
    currentPlayer(1) {
    initializePlayers();
}

void Game::resetGame() {
    board = GameBoard(board.getSize()); // Resetează tabla
    player1.wizard.resetGame();
    player2.wizard.resetGame();
    currentPlayer = 1; // Opțional, setăm primul jucător
}