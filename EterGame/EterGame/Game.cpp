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

void Game::start() {
    while (true) {
        board.printBoard();
        Player& activePlayer = (currentPlayer == 1) ? player1 : player2;

        // Utilizarea abilitatii
        std::cout << activePlayer.name << ", do you want to use your wizard's ability? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "yes") {
            try {
                if (activePlayer.wizard.power == MagicPower::REMOVE_ROW_WITH_OWN_CARD) {
                    std::cout << "Enter the row to remove: ";
                    int row;
                    std::cin >> row;

                    activePlayer.wizard.useAbility(board, row, -1, activePlayer);

                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN) {
                    std::cout << "Enter the row and column of the card to remove: ";
                    int row, col;
                    std::cin >> row >> col;

                    activePlayer.wizard.useAbility(board, row, col, activePlayer);

                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::COVER_OPPONENT_CARD) {
                    std::cout << "Enter the row and column of the opponent's card to cover: ";
                    int row, col;
                    std::cin >> row >> col;

                    activePlayer.wizard.useAbility(board, row, col, activePlayer);

                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::CREATE_HOLE) {
                    std::cout << "Enter the row and column of the empty space to transform into a hole: ";
                    int row, col;
                    std::cin >> row >> col;

                    try {
                        activePlayer.wizard.useAbility(board, row, col, activePlayer);
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    }
                    catch (const std::exception& e) {
                        std::cout << e.what() << "\n";
                    }
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::MOVE_STACK_WITH_OWN_CARD) {
                    std::cout << "Enter the source row and column of the stack to move: ";
                    int srcRow, srcCol;
                    std::cin >> srcRow >> srcCol;

                    std::cout << "Enter the destination row and column for the stack: ";
                    int destRow, destCol;
                    std::cin >> destRow >> destCol;

                    try {
                        activePlayer.wizard.useAbility(board, srcRow, srcCol, activePlayer, destRow, destCol);
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    }
                    catch (const std::exception& e) {
                        std::cout << e.what() << "\n";
                    }
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::GAIN_EXTRA_CARD) {
                    std::cout << "Enter the row and column to place the Ether card: ";
                    int row, col;
                    std::cin >> row >> col;

                    try {
                        activePlayer.wizard.useAbility(board, row, col, activePlayer);
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    }
                    catch (const std::exception& e) {
                        std::cout << e.what() << "\n";
                    }
                    continue;
                }
                else if (activePlayer.wizard.power == MagicPower::MOVE_STACK_WITH_OPPONENT_CARD) {
                    std::cout << "Enter the source row and column of the stack to move: ";
                    int srcRow, srcCol;
                    std::cin >> srcRow >> srcCol;

                    std::cout << "Enter the destination row and column for the stack: ";
                    int destRow, destCol;
                    std::cin >> destRow >> destCol;

                    try {
                        activePlayer.wizard.useAbility(board, srcRow, srcCol, activePlayer, destRow, destCol);
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    }
                    catch (const std::exception& e) {
                        std::cout << e.what() << "\n";
                    }
                    continue;
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                continue;
            }
        }

        std::cout << activePlayer.name << "'s turn. Select row and column (e.g., 1 1): ";
        int row, col;
        validateInput(row, col);

        std::cout << "Select card index from hand (1-" << activePlayer.hand.size() << "): ";
        int cardIndex;
        std::cin >> cardIndex;
        cardIndex -= 1; // Ajustare pentru vectorul intern
        validateCardIndex(cardIndex, activePlayer);

        if (cardIndex >= 0 && cardIndex < activePlayer.hand.size()) {
            Card card = activePlayer.hand[cardIndex];
            if (board.placeCard(row, col, card, activePlayer)) {
                activePlayer.removeCard(cardIndex);

                // Activează explozia, dacă e cazul
                if (board.triggerExplosion(activePlayer)) {
                    continue;
                }

                // Verifică condiția de câștig
                std::string winCondition = board.checkWinCondition(activePlayer);
                if (!winCondition.empty()) {
                    std::cout << activePlayer.name << " wins by " << winCondition << "!\n";
                    break;
                }

                // Schimbă rândul jucătorului
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
            else {
                std::cout << "Invalid move. Try again.\n";
            }
        }
    }


}