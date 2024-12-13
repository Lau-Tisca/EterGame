#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

void clearConsole();

// Mod antrenament
void trainingMode();
// Duel vrajitori
void wizardsDuel();
//Duel elemente

// Modul turneu


int main() {
    /*

    Wizard wizard1("Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD);
    Wizard wizard2("Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN);

    Game game(3, "Player1", "Player2", wizard1, wizard2);
    game.start();
    */
    srand(static_cast<unsigned>(time(0)));

    unsigned short int choice = 0;

    do {
        clearConsole();
        std::cout << "/------------------------------------\\\n";
        std::cout << "| What gamemode do you want to play? |\n";
        std::cout << "| 1. Training Mode                   |\n";
        std::cout << "| 2. Wizard's Duel                   |\n";
        std::cout << "| 3. Element's Duel                  |\n";
        std::cout << "| 4. Tournament                      |\n";
        std::cout << "| 5. Speed Mode                      |\n";
        std::cout << "| 6. Exit Game                       |\n";
        std::cout << "\\------------------------------------/\n\n";

        std::cout << "Choice: ";
        if (!(std::cin >> choice)) {
            // Dacă intrarea nu este numerică
            std::cin.clear();                // Curățăm starea de eroare
            std::cin.ignore(1000, '\n');     // Golim bufferul până la finalul liniei
            std::cout << "\nInvalid input. Please enter a number between 1 and 6.\n\n";
            continue;                        // Reia bucla
        }

        std::cout << '\n';

        switch (choice) {
        case 1:
            trainingMode();
            break;
        case 2:
            wizardsDuel();
            break;
        case 3:
            //elementsDuel();
            break;
        case 4:
            //tournamentMode();
            break;
        case 5:
            //speedMode();
            break;
        case 6:
            std::cout << "Leaving Game.\n\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n\n";
            break;
        }
    } while (choice != 6);

    return 0;
}

void clearConsole() {
    system("CLS");
    /*
    // Adaugare debug

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Invalid handle\n";
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Error: Unable to get console screen buffer info\n";
        return;
    }

    DWORD consoleSize;
    DWORD charsWritten;

    if (!FillConsoleOutputCharacter(hConsole, ' ', consoleSize, { 0, 0 }, &charsWritten)) {
        std::cerr << "Error: Unable to fill console output character\n";
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, { 0, 0 }, &charsWritten)) {
        std::cerr << "Error: Unable to fill console output attribute\n";
        return;
    }

    if (!SetConsoleCursorPosition(hConsole, { 0, 0 })) {
        std::cerr << "Error: Unable to set console cursor position\n";
        return;
    }

    // Obține dimensiunea bufferului consolei
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Umple bufferul cu spații
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, { 0, 0 }, &charsWritten);

    // Resetează atributele consolei
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, { 0, 0 }, &charsWritten);

    // Mutați cursorul la început
    SetConsoleCursorPosition(hConsole, { 0, 0 });*/
}

// Mod antrenament
void trainingMode() {
    clearConsole();
    std::cout << "Starting Training Mode...\n";

    // Crearea vrăjitorilor "default" pentru acest mod
    Wizard wizard1(u8"Training Wizard 1", MagicPower::GAIN_EXTRA_CARD);
    Wizard wizard2(u8"Training Wizard 2", MagicPower::MOVE_ROW_TO_EDGE);

    // Crearea jocului cu tabla 3x3
    Game game(3, "Player 1", "Player 2", wizard1, wizard2);
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));

    // Formatul 2/3
    int player1Wins = 0;
    int player2Wins = 0;

    // Configurarea cărților pentru jucători
    //1 card
    std::cout << "Player 1: Place first card.   Select card index from hand (1-" << game.getPlayer1().hand.size() << "): \n";
    for (int i = 0; i < game.getPlayer1().hand.size(); i++)
        if (!game.getPlayer1().hand[i].isIllusion)
            std::cout << "[" << i + 1 << "]:" << game.getPlayer1().hand[i] << " ";
    std::cout << "\n";


    int cardIndex;
    std::cin >> cardIndex;
    while (cardIndex < 0 || cardIndex >= game.getPlayer1().hand.size()) {
        std::cout << "Invalid card index!\n";
        std::cin >> cardIndex;
    }
    cardIndex -= 1; // Ajustare pentru vectorul intern

    Card card = game.getPlayer1().hand[cardIndex];

    try {
        if (game.getBoard().placeCard(1, 1, card, game.getPlayer1())) {
            game.getPlayer1().removeCard(cardIndex); // Elimină cartea din mână

            // Verificare regulă iluzie
            if (card.isIllusion && game.getBoard().checkIllusionRule(1, 1, game.getPlayer2())) {
                std::cout << "Illusion revealed! Opponent's turn ends.\n";
            }
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    //2 card
    std::cout << "Player 2: Place second card.   Select card index from hand (1-" << game.getPlayer2().hand.size() << "): \n";
    for (int i = 0; i < game.getPlayer2().hand.size(); i++)
        if (!game.getPlayer2().hand[i].isIllusion)
            std::cout << "[" << i + 1 << "]:" << game.getPlayer2().hand[i] << " ";
    std::cout << "\n";

    std::cin >> cardIndex;
    while (cardIndex < 0 || cardIndex >= game.getPlayer2().hand.size()) {
        std::cout << "Invalid card index!\n";
        std::cin >> cardIndex;
    }
    cardIndex -= 1; // Ajustare pentru vectorul intern

    card = game.getPlayer2().hand[cardIndex];

    game.getBoard().printBoard();
    std::cout << game.getPlayer2().name << "'s turn. Select row and column (e.g., 1 1): ";
    int row, col;
    std::cin >> row >> col;
    while ((int)row != row || (int)col != col)
    {
        std::cout << "Insert correct coordinates!\n";
        std::cin >> row >> col;
    }

    try {
        if (game.getBoard().placeCard(row, col, card, game.getPlayer2())) {
            game.getPlayer2().removeCard(cardIndex); // Elimină cartea din mână

            // Verificare regulă iluzie
            if (card.isIllusion && game.getBoard().checkIllusionRule(row, col, game.getPlayer1())) {
                std::cout << "Illusion revealed! Opponent's turn ends.\n";
            }
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    while (player1Wins < 2 && player2Wins < 2) {
        //system("CLS");
        //game.resetGame(); // Resetează jocul pentru un nou meci
        game.start();     // Începe runda

        std::string winConditionP1 = game.getBoard().checkWinCondition(game.getPlayer1());
        if (winConditionP1 != "")
        {
            player1Wins++;

            std::cout << game.getPlayer1().getName() << " WINS!\n";
        }

        std::string winConditionP2 = game.getBoard().checkWinCondition(game.getPlayer2());
        if (winConditionP2 != "")
        {
            player2Wins++;

            std::cout << game.getPlayer2().getName() << " WINS!\n";
        }

        if (player1Wins == 2) {
            std::cout << game.getPlayer1().getName() << " wins the training mode!\n";
            return;
        }
        else if (player2Wins == 2) {
            std::cout << game.getPlayer2().getName() << " wins the training mode!\n";
            return;
        }
    }
}

void wizardsDuel() {
    std::cout << "Starting Wizard's Duel...\n";

    // Randomizare vrăjitori
    srand(static_cast<unsigned>(time(0))); // Inițializare pentru rand()
    int index1 = rand() % availableWizards.size();
    int index2;
    do {
        index2 = rand() % availableWizards.size();
    } while (index1 == index2); // Asigură-te că vrăjitorii sunt diferiți

    Wizard wizard1 = availableWizards[index1];
    Wizard wizard2 = availableWizards[index2];

    // Configurare joc
    Game game(4, "Player 1", "Player 2", wizard1, wizard2);

    // Configurare cărți pentru fiecare jucător
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(1));
        game.getPlayer2().addCard(Card(1));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(2));
        game.getPlayer2().addCard(Card(2));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));
    game.getPlayer1().addCard(Card(0, false, true)); // Eter
    game.getPlayer2().addCard(Card(0, false, true)); // Eter

    // Format meci: 3/5
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < 3 && player2Wins < 3) {
        game.resetGame();
        game.start();

        // Determină câștigătorul și actualizează scorul
        int score1 = game.getBoard().calculateScore(game.getPlayer1());
        int score2 = game.getBoard().calculateScore(game.getPlayer2());

        if (score1 > score2) {
            std::cout << game.getPlayer1().getName() << " wins this game!\n";
            ++player1Wins;
        }
        else if (score2 > score1) {
            std::cout << game.getPlayer2().getName() << " wins this game!\n";
            ++player2Wins;
        }
        else {
            std::cout << "This game is a tie!\n";
        }

        std::cout << "Current score: " << game.getPlayer1().getName() << " " << player1Wins
            << " - " << player2Wins << " " << game.getPlayer2().getName() << "\n";
    }

    // Determină câștigătorul meciului
    if (player1Wins == 3) {
        std::cout << game.getPlayer1().getName() << " wins the match!\n";
    }
    else {
        std::cout << game.getPlayer2().getName() << " wins the match!\n";
    }
}
