#include <iostream>
#include "Game.h"
#include "Wizard.h"
#include "MagicPower.h"

void trainingMode();
void wizardsDuel();

int main() {
    srand(static_cast<unsigned>(time(0)));

    Wizard wizard1(u8"Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD);
    Wizard wizard2(u8"Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN);

    Game game(3, "Player1", "Player2", wizard1, wizard2);
    game.start();


	return 0;
}

void trainingMode() {
    std::cout << "Starting Training Mode...\n";

    // Crearea vrăjitorilor "default" pentru acest mod
    Wizard wizard1("Training Wizard 1", MagicPower::GAIN_EXTRA_CARD);
    Wizard wizard2("Training Wizard 2", MagicPower::MOVE_ROW_TO_EDGE);

    // Crearea jocului cu tabla 3x3
    Game game(3, "Player 1", "Player 2", wizard1, wizard2);

    // Configurarea cărților pentru jucători
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(1));
        game.getPlayer2().addCard(Card(1));
        game.getPlayer1().addCard(Card(2));
        game.getPlayer2().addCard(Card(2));
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));

    // Formatul 2/3
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < 2 && player2Wins < 2) {
        game.resetGame(); // Resetează jocul pentru un nou meci
        game.start();     // Începe jocul

        // Calcularea scorurilor
        int player1Score = game.getBoard().calculateScore(game.getPlayer1());
        int player2Score = game.getBoard().calculateScore(game.getPlayer2());

        if (player1Score > player2Score) {
            std::cout << game.getPlayer1().getName() << " wins this game!\n";
            ++player1Wins;
        }
        else if (player2Score > player1Score) {
            std::cout << game.getPlayer2().getName() << " wins this game!\n";
            ++player2Wins;
        }
        else {
            std::cout << "This game is a tie!\n";
        }

        std::cout << "Current Score: " << game.getPlayer1().getName() << " " << player1Wins
            << " - " << player2Wins << " " << game.getPlayer2().getName() << "\n\n";
    }

    if (player1Wins == 2) {
        std::cout << game.getPlayer1().getName() << " wins the training mode!\n";
    }
    else {
        std::cout << game.getPlayer2().getName() << " wins the training mode!\n";
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
