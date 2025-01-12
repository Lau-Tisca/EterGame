#include <iostream>
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"
#include <limits>
#include <stdexcept>

Game::Game(int boardSize, const std::string& player1Name, const std::string& player2Name,
    const Wizard& wizard1, const Wizard& wizard2, GameMode mode)
    : board(boardSize, player1, player2),
    player1(player1Name, wizard1), // Jucătorul 1 primește un vrăjitor
    player2(player2Name, wizard2), // Jucătorul 2 primește un vrăjitor
    currentPlayer(1),
    currentMode(mode)
{
    std::cout << "Game initialized with players: "
        << player1Name << " and " << player2Name
        << " in mode: "
        << (mode == GameMode::Training ? "Training" :
            mode == GameMode::WizardsDuel ? "Wizard's Duel" :
            "Elements Duel")
        << ".\n";
}


void Game::resetPlayerHand(Player& player) {
    // Golește mâna actuală
    player.hand.clear();

    // Adaugă cărțile inițiale (în funcție de mod sau reguli)
    switch (currentMode) {
    case GameMode::Training:
        player.addCard(Card(1));
        player.addCard(Card(1));
        player.addCard(Card(2));
        player.addCard(Card(2));
        player.addCard(Card(3));
        player.addCard(Card(3));
        player.addCard(Card(4));
        break;

    case GameMode::WizardsDuel:
        player.addCard(Card(1));
        player.addCard(Card(1));
        player.addCard(Card(2));
        player.addCard(Card(2));
        player.addCard(Card(2));
        player.addCard(Card(3));
        player.addCard(Card(3));
        player.addCard(Card(3));
        player.addCard(Card(4));
        player.addCard(Card(0, false, true)); // Ether card
        break;

    case GameMode::ElementsDuel:
        player.addCard(Card(1));
        player.addCard(Card(2));
        player.addCard(Card(2));
        player.addCard(Card(2));
        player.addCard(Card(3));
        player.addCard(Card(3));
        player.addCard(Card(3));
        player.addCard(Card(4));
        player.addCard(Card(0, false, true)); // Eter
        break;
    }

    std::cout << player.getName() << "'s hand has been reset for mode: "
        << (currentMode == GameMode::Training ? "Training" :
            currentMode == GameMode::WizardsDuel ? "Wizards Duel" : "Elements Duel") << ".\n";

    //std::cout << player.getName() << "'s hand has been reset.\n";
}

void Game::resetGame() {
    board = GameBoard(board.getSize(), player1, player2); // Resetează tabla
    board.setFirstMove(true); // Resetează flag-ul de prima mutare

    // Reseteaza vrajitorii pentru un nou joc
    player1.resetWizardForGame();
    player2.resetWizardForGame();

    // Resetează mâinile jucătorilor conform modului curent
    switch (currentMode) {
    case GameMode::Training:
        resetPlayerHand(player1);
        resetPlayerHand(player2);
        break;

    case GameMode::WizardsDuel:
        resetPlayerHand(player1);
        resetPlayerHand(player2);
        player1.setWizard(Wizard::getRandomWizard());
        player2.setWizard(Wizard::getRandomWizardDistinctFrom(player1.getWizard()));
        break;

    case GameMode::ElementsDuel:
        resetPlayerHand(player1);
        resetPlayerHand(player2);
        break;
    }

    // Setează jucătorul curent la primul jucător
    currentPlayer = 1;

    std::cout << "Game reset for mode: "
        << (currentMode == GameMode::Training ? "Training" :
            currentMode == GameMode::WizardsDuel ? "Wizards Duel" : "Elements Duel") << ".\n";

    //std::cout << "Game reset. Ready for the next round!\n";
}

void Game::start() {
    while (true) {
        while (true) {
            board.printBoard();
            Player& activePlayer = (currentPlayer == 1) ? player1 : player2;

            // oponent
            Player& opponent = (currentPlayer == 1) ? player2 : player1;

            // Utilizarea abilitatii vrajitorului
            std::cout << activePlayer.name << ", do you want to use your wizard's ability? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            while (choice != "yes" && choice != "no") {
                std::cout << "Invalid input! Please answer 'yes' or 'no': ";
                std::cin >> choice;
            }

            if (choice == "yes") {
                if (activePlayer.wizard.usedThisMatch) {
                    std::cout << "The magical power has already been used this match!\n";
                }
                else {
                    try {
                        if (activePlayer.wizard.power == MagicPower::REMOVE_ROW_WITH_OWN_CARD) {
                            int row;
                            while (true) {
                                std::cout << "Enter the row to remove: ";
                                std::cin >> row;
                                if (std::cin.fail() || row < 0 || row >= board.getSize()) {
                                    std::cout << "Invalid row. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, row, -1);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN) {
                            int row, col;
                            while (true) {
                                std::cout << "Enter the row and column of the card to remove: ";
                                std::cin >> row >> col;
                                if (std::cin.fail() || row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                                    std::cout << "Invalid input. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::COVER_OPPONENT_CARD) {
                            int row, col;
                            while (true) {
                                std::cout << "Enter the row and column of the opponent's card to cover: ";
                                std::cin >> row >> col;
                                if (std::cin.fail() || row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                                    std::cout << "Invalid input. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }

                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }

                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::CREATE_HOLE) {
                            int row, col;
                            while (true) {
                                std::cout << "Enter the row and column of the empty space to transform into a hole: ";
                                std::cin >> row >> col;
                                if (std::cin.fail() || row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                                    std::cout << "Invalid input. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }

                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }

                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::MOVE_STACK_WITH_OWN_CARD) {
                            int srcRow, srcCol, destRow, destCol;
                            while (true) {
                                std::cout << "Enter the source row and column of the stack to move: ";
                                std::cin >> srcRow >> srcCol;
                                if (std::cin.fail() || srcRow < 0 || srcRow >= board.getSize() || srcCol < 0 || srcCol >= board.getSize()) {
                                    std::cout << "Invalid input for source. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            while (true) {
                                std::cout << "Enter the destination row and column for the stack: ";
                                std::cin >> destRow >> destCol;
                                if (std::cin.fail() || destRow < 0 || destRow >= board.getSize() || destCol < 0 || destCol >= board.getSize()) {
                                    std::cout << "Invalid input for destination. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, srcRow, srcCol, destRow, destCol);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::GAIN_EXTRA_CARD) {
                            int row, col;
                            while (true) {
                                std::cout << "Enter the row and column to place the Ether card: ";
                                std::cin >> row >> col;
                                if (std::cin.fail() || row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
                                    std::cout << "Invalid input. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                        else if (activePlayer.wizard.power == MagicPower::MOVE_STACK_WITH_OPPONENT_CARD) {
                            int srcRow, srcCol, destRow, destCol;
                            while (true) {
                                std::cout << "Enter the source row and column of the stack to move: ";
                                std::cin >> srcRow >> srcCol;
                                if (std::cin.fail() || srcRow < 0 || srcRow >= board.getSize() || srcCol < 0 || srcCol >= board.getSize()) {
                                    std::cout << "Invalid input for source. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            while (true) {
                                std::cout << "Enter the destination row and column for the stack: ";
                                std::cin >> destRow >> destCol;
                                if (std::cin.fail() || destRow < 0 || destRow >= board.getSize() || destCol < 0 || destCol >= board.getSize()) {
                                    std::cout << "Invalid input for destination. Try again.\n";
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                                else {
                                    break;
                                }
                            }
                            try {
                                activePlayer.wizard.useAbility(board, activePlayer, opponent, srcRow, srcCol, destRow, destCol);
                            }
                            catch (const std::exception& e) {
                                std::cout << e.what() << "\n";
                            }
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                        }
                    }
                    catch (const std::exception& e) {
                        std::cout << e.what() << "\n";
                    }
                }
                // Schimbă jucătorul chiar dacă abilitatea nu este folosită corect
                currentPlayer = (currentPlayer == 1) ? 2 : 1;

                continue;
            }

            // Alege între plasarea unei iluzii sau a unei cărți normale
            std::cout << "Do you want to place an illusion? (yes/no): ";
            std::cin >> choice;

            while (choice != "yes" && choice != "no") {
                std::cout << "Invalid input! Please answer 'yes' or 'no': ";
                std::cin >> choice;
            }

            if (choice == "yes") {
                if (placeIllusion(activePlayer, board)) {
                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
                    continue;
                }
            }

            // Plasarea unei cărți normale
            if (placeNormalCard(activePlayer, board, opponent)) {
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

                currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă rândul
            }
        }

        // Calcularea scorului la finalul jocului
        int score1 = board.calculateScore(player1);
        int score2 = board.calculateScore(player2);

        std::cout << "\nFinal scores:\n";
        std::cout << player1.name << ": " << score1 << " points\n";
        std::cout << player2.name << ": " << score2 << " points\n";

        if (score1 > score2) {
            std::cout << player1.name << " wins the game!\n";
        }
        else if (score2 > score1) {
            std::cout << player2.name << " wins the game!\n";
        }
        else {
            std::cout << "The game is a tie!\n";
        }
    }

}

void Game::validateInput(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-" << board.getSize() - 1 << "): ";
        if (std::cin >> row >> col && row >= 0 && row < board.getSize() && col >= 0 && col < board.getSize()) {
            break;
        }
        else {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear(); // Curăță eroarea
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei
        }
    }
}

void Game::validateCardIndex(int& index, const Player& player) {
    while (index < 0 || index >= player.hand.size()) {
        std::cout << "Invalid card index! Enter a valid index (1-" << player.hand.size() << "): ";
        std::cin >> index;
        index -= 1; // Ajustează indexul pentru a începe de la 0
    }
}



bool Game::placeIllusion(Player& activePlayer, GameBoard& board) {
    if (activePlayer.hasPlacedIllusion) {
        std::cout << "You have already placed an Illusion this game!\n";
        return false; // Jucătorul nu poate plasa altă iluzie
    }

    std::cout << "Select card index from hand (1-" << activePlayer.hand.size() << "): \n";
    for (int i = 0; i < activePlayer.hand.size(); i++)
        if (!activePlayer.hand[i].isIllusion)
            std::cout << "[" << i + 1 << "]:" << activePlayer.hand[i] << " ";
    std::cout << "\n";

    int cardIndex;
    std::cin >> cardIndex;
    cardIndex -= 1; // Ajustare pentru vectorul intern

    if (cardIndex < 0 || cardIndex >= activePlayer.hand.size()) {
        std::cout << "Invalid card index!\n";
        return false;
    }

    // Obtine cartea selectata
    Card card = activePlayer.hand[cardIndex];
    card.isIllusion = true; // Marchează ca fiind iluzie

    // Alegerea poziției
    std::cout << activePlayer.name << "'s turn. Select row and column (e.g., 1 1): ";
    int row, col;
    std::cin >> row >> col;

    try {
        if (board.placeCard(row, col, 0, card, activePlayer)) {
            activePlayer.removeCard(cardIndex); // Elimină cartea din mână
            activePlayer.hasPlacedIllusion = true; // Marchează utilizarea iluziilor
            std::cout << "Illusion placed successfully at (" << row << ", " << col << ").\n";
            return true; // Plasarea a fost reușită
        }
        else {
            std::cout << "Invalid move. Cannot place an illusion there.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return false; // Plasarea a eșuat
}

bool Game::placeNormalCard(Player& activePlayer, GameBoard& board, Player& opponent) {
    std::cout << "Select card index from hand (1-" << activePlayer.hand.size() << "): \n";
    for (int i = 0; i < activePlayer.hand.size(); i++)
        if (!activePlayer.hand[i].isIllusion)
            std::cout << "[" << i + 1 << "]:" << activePlayer.hand[i] << " ";
    std::cout << "\n";

    int cardIndex;
    std::cin >> cardIndex;
    cardIndex -= 1; // Ajustare pentru vectorul intern

    if (cardIndex < 0 || cardIndex >= activePlayer.hand.size()) {
        std::cout << "Invalid card index!\n";
        return false;
    }

    Card card = activePlayer.hand[cardIndex];
    std::cout << "Selected card value: " << card.value << "\n";

    int row, col;
    std::cout << activePlayer.name << "'s turn. Select row and column (e.g., 1 1): ";
    std::cin >> row >> col;

    std::cout << "Attempting to place card...\n";
    if (board.placeCard(row, col, 0, card, activePlayer)) {
        std::cout << "Card placed successfully.\n";
        activePlayer.removeCard(cardIndex); // Elimină cartea din mână
        return true;
    }
    else {
        std::cout << "Failed to place card.\n";
        return false;
    }
}

GameBoard& Game::getBoard() {
    return board;
}

Player& Game::getPlayer1() {
    return player1;
}

Player& Game::getPlayer2() {
    return player2;
}


