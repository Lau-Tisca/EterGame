#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <fstream>

using json = nlohmann::json;

Game::Game(int boardSize,
    const std::string& player1Name,
    const std::string& player2Name,
    const Wizard& wizard1,
    const Wizard& wizard2,
    GameMode mode)
    : board(boardSize, player1, player2),
    player1(player1Name, wizard1),
    player2(player2Name, wizard2),
    currentPlayer(1),
    currentMode(mode),
    isWizardsDuel(mode == GameMode::WizardsDuel),
    isElementalDuel(mode == GameMode::ElementsDuel),
    isTournamentMode(mode == GameMode::Tournament), // Adăugat Tournament Mode
    player1Markers(0),
    player2Markers(0),
    battleArena(3, std::vector<int>(3, 0)) // Inițializează arena 3x3 goală
{
    std::cout << "Game initialized with players: "
        << player1Name << " and " << player2Name
        << " in mode: "
        << (mode == GameMode::Training ? "Training" :
            mode == GameMode::WizardsDuel ? "Wizard's Duel" :
            mode == GameMode::ElementsDuel ? "Elements Duel" :
            "Pure Tournament")
        << ".\n";
}

Game::Game(int boardSize,
    const std::string& player1Name,
    const std::string& player2Name,
    GameMode mode)
    : board(boardSize, player1, player2),
    player1(player1Name, Wizard()),   // Adăugat wizard implicit
    player2(player2Name, Wizard()),
    currentPlayer(1),
    currentMode(mode),
    isWizardsDuel(mode == GameMode::WizardsDuel),
    isElementalDuel(mode == GameMode::ElementsDuel),
    isTournamentMode(mode == GameMode::Tournament), // Adăugat Tournament Mode
    player1Markers(0),
    player2Markers(0),
    battleArena(3, std::vector<int>(3, 0)) // Inițializează arena 3x3 goală
{
    std::cout << "Game initialized for "
        << (mode == GameMode::ElementsDuel ? "Elements Duel" : mode == GameMode::Tournament ? "Pure Tournament" : "another mode")
        << " with players: " << player1Name << " and " << player2Name << ".\n";
}

nlohmann::json Game::toJson() const {
    json saveData;
    saveData["currentRound"] = currentRound;
    saveData["gameMode"] = static_cast<int>(currentMode);

    json player1Data, player2Data;
    player1Data["name"] = player1.getName();
    for (const Card& card : player1.getHand()) {
        player1Data["hand"].push_back(card.value);
    }

    player2Data["name"] = player2.getName();
    for (const Card& card : player2.getHand()) {
        player2Data["hand"].push_back(card.value);
    }

    saveData["players"] = { player1Data, player2Data };
    saveData["board"] = board.toJson();

    std::cout << "[DEBUG] Saving JSON: " << saveData.dump(4) << "\n";
    return saveData;
}


void Game::fromJson(const json& jsonData) {
    currentRound = jsonData["currentRound"];
    currentMode = static_cast<GameMode>(jsonData["gameMode"]);

    player1 = Player(jsonData["players"][0]["name"]);
    player2 = Player(jsonData["players"][1]["name"]);

    for (const auto& cardValue : jsonData["players"][0]["hand"]) {
        player1.addCard(Card(cardValue));
    }

    for (const auto& cardValue : jsonData["players"][1]["hand"]) {
        player2.addCard(Card(cardValue));
    }

    board.fromJson(jsonData["board"]);
}

void Game::saveGameState(const std::string& filename) const {
    std::cout << "[DEBUG] Trying to save game to: " << filename << "\n";

    json saveData;
    saveData["currentRound"] = currentRound;
    saveData["gameMode"] = static_cast<int>(currentMode);

    json player1Data, player2Data;
    player1Data["name"] = player1.getName();
    player2Data["name"] = player2.getName();

    for (const auto& card : player1.getHand()) {
        player1Data["hand"].push_back(card.value);
    }

    for (const auto& card : player2.getHand()) {
        player2Data["hand"].push_back(card.value);
    }

    saveData["players"] = { player1Data, player2Data };
    saveData["board"] = board.toJson();

    std::cout << "[DEBUG] JSON content before writing:\n" << saveData.dump(4) << "\n";

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] Failed to open save file! Check permissions or path.\n";
        return;
    }

    file << saveData.dump(4);
    file.close();

    std::cout << "[DEBUG] Game saved successfully to " << filename << "!\n";
}


bool Game::loadGameState(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "[ERROR] No saved game found!\n";
        return false;
    }

    json saveData;
    try {
        file >> saveData;
        file.close();
    }
    catch (...) {
        std::cerr << "[ERROR] Failed to parse savegame.json. Starting a new game.\n";
        return false;
    }

    std::cout << "[DEBUG] Loaded JSON: " << saveData.dump(4) << "\n";

    currentRound = saveData["currentRound"];
    currentMode = static_cast<GameMode>(saveData["gameMode"]);

    player1 = Player(saveData["players"][0]["name"]);
    player2 = Player(saveData["players"][1]["name"]);

    for (const auto& cardValue : saveData["players"][0]["hand"]) {
        player1.addCard(Card(cardValue));
    }

    for (const auto& cardValue : saveData["players"][1]["hand"]) {
        player2.addCard(Card(cardValue));
    }

    board.fromJson(saveData["board"]);

    std::cout << "[DEBUG] Game loaded successfully!\n";
    return true;
}



void Game::startTournament() {
    int player1Score = 0;
    int player2Score = 0;

    int roundsPlayed = 0;
    while (roundsPlayed < 5) {
        std::cout << "\n=== Round " << (roundsPlayed + 1) << " ===\n";
        board.resetBoard();
        player1.resetHand();
        player2.resetHand();
        currentPlayer = 1;

        // Distribuie cărți jucătorilor
        for (int i = 0; i < 2; i++) {
            player1.addCard(Card(1));
            player2.addCard(Card(1));
        }
        for (int i = 0; i < 2; i++) {
            player1.addCard(Card(2));
            player2.addCard(Card(2));
        }
        for (int i = 0; i < 2; i++) {
            player1.addCard(Card(3));
            player2.addCard(Card(3));
        }
        player1.addCard(Card(4));
        player2.addCard(Card(4));

        while (true) {
            board.printBoard();
            Player& activePlayer = (currentPlayer == 1) ? player1 : player2;
            Player& opponent = (currentPlayer == 1) ? player2 : player1;

            std::cout << activePlayer.getName() << "'s turn.\n";
            std::cout << "[DEBUG] " << activePlayer.getName() << " hand size: " << activePlayer.hand.size() << "\n";

            // Afișează scorul după fiecare mutare
            int player1Markers = 0, player2Markers = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (battleArena[row][col] == 1) player1Markers++;
                    else if (battleArena[row][col] == 2) player2Markers++;
                }
            }
            std::cout << "\n[TOURNAMENT SCORE] "
                << player1.getName() << ": " << player1Markers
                << " | " << player2.getName() << ": " << player2Markers << "\n";

            // Întrebare despre iluzie
            std::string choice;
            std::cout << "Do you want to place an illusion? (yes/no): ";
            std::cin >> choice;

            while (choice != "yes" && choice != "no") {
                std::cout << "Invalid input! Please answer 'yes' or 'no': ";
                std::cin >> choice;
            }

            if (choice == "yes") {
                // Jucătorul alege valoarea iluziei
                std::cout << "Your hand: ";
                for (size_t i = 0; i < activePlayer.hand.size(); ++i) {
                    std::cout << "[" << i + 1 << ": " << activePlayer.hand[i].value << "] ";
                }
                std::cout << "\nChoose a card to use as an illusion (1-" << activePlayer.hand.size() << "): ";

                int cardIndex;
                while (true) {
                    std::cin >> cardIndex;
                    if (cardIndex >= 1 && cardIndex <= static_cast<int>(activePlayer.hand.size())) {
                        break;
                    }
                    std::cout << "Invalid choice! Choose a valid card index: ";
                }

                Card illusionCard = activePlayer.hand[cardIndex - 1];
                illusionCard.isIllusion = true;

                int row, col;
                std::cout << "Enter row and column: ";
                std::cin >> row >> col;

                if (board.placeTCard(row, col, 0, illusionCard, activePlayer)) {
                    std::cout << "[INFO] Illusion placed at (" << row << ", " << col << ") with value " << illusionCard.value << ".\n";
                    activePlayer.removeCard(cardIndex - 1);
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    continue; // Sare la runda următoare
                }
                else {
                    std::cerr << "[ERROR] Invalid illusion placement! Try again.\n";
                    continue;
                }
            }

            // Afișează cărțile din mână și permite alegerea uneia
            std::cout << "Your hand: ";
            for (size_t i = 0; i < activePlayer.hand.size(); ++i) {
                std::cout << "[" << i + 1 << ": " << activePlayer.hand[i].value << "] ";
            }
            std::cout << "\nChoose a card (1-" << activePlayer.hand.size() << "): ";

            int cardIndex;
            while (true) {
                std::cin >> cardIndex;
                if (cardIndex >= 1 && cardIndex <= static_cast<int>(activePlayer.hand.size())) {
                    break;
                }
                std::cout << "Invalid choice! Choose a valid card index: ";
            }

            Card selectedCard = activePlayer.hand[cardIndex - 1];

            int row, col;
            std::cout << "Enter row and column: ";
            std::cin >> row >> col;

            std::cout << "[DEBUG] Attempting to place card " << selectedCard.value << " at (" << row << ", " << col << ")\n";
            if (board.placeTCard(row, col, 0, selectedCard, activePlayer)) {
                activePlayer.removeCard(cardIndex - 1);  // Elimină cartea din mână după plasare

                std::string winCondition = board.checkWinCondition(activePlayer);
                if (!winCondition.empty()) {
                    std::cout << activePlayer.getName() << " wins this round!\n";
                    placeMarker(row, col, currentPlayer);

                    // ✅ Adaugă un punct câștigătorului
                    if (currentPlayer == 1) {
                        player1Score++;
                    }
                    else {
                        player2Score++;
                    }

                    // ✅ Verifică dacă cineva a ajuns la 5 puncte
                    if (player1Score >= 5) {
                        std::cout << "[🏆] " << player1.getName() << " wins the Tournament with 5 points!\n";
                        return;
                    }
                    else if (player2Score >= 5) {
                        std::cout << "[🏆] " << player2.getName() << " wins the Tournament with 5 points!\n";
                        return;
                    }

                    break;
                }
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
            else {
                std::cerr << "[ERROR] Invalid move! Try again.\n";
            }
        }

        roundsPlayed++;
    }
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

void Game::checkForExplosion(int lastMoveRow, int lastMoveCol) {
    Player& activePlayer = (currentPlayer == 1) ? player1 : player2;

    if (!board.canTriggerExplosion()) {
        std::cout << "[INFO] Not enough full lines to trigger an explosion.\n";
        return;
    }

    std::cout << activePlayer.getName() << ", do you want to trigger an explosion? (yes/no): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "yes") {
        board.triggerExplosion(activePlayer);
        std::cout << "[INFO] Explosion triggered successfully!\n";
    }
    else {
        std::cout << "[INFO] Explosion skipped.\n";
    }
}

void Game::placeMarker(int row, int col, int player) {
    int& markerCount = (player == 1) ? player1Markers : player2Markers;

    if (battleArena[row][col] == 0) {
        battleArena[row][col] = player; // Plasează marker nou
    }
    else if (battleArena[row][col] != player) {
        battleArena[row][col] = player; // Înlocuiește markerul adversarului
    }
    else {
        markerCount++; // Crește numărul de markere ale jucătorului
    }

    std::cout << "[BATTLE ARENA] Player " << player << " placed a marker at (" << row << ", " << col << ").\n";
}

bool Game::checkTournamentWin(int player) {
    for (int i = 0; i < 3; i++) {
        if ((battleArena[i][0] == player && battleArena[i][1] == player && battleArena[i][2] == player) || // Linie
            (battleArena[0][i] == player && battleArena[1][i] == player && battleArena[2][i] == player)) { // Coloană
            return true;
        }
    }

    if ((battleArena[0][0] == player && battleArena[1][1] == player && battleArena[2][2] == player) ||
        (battleArena[0][2] == player && battleArena[1][1] == player && battleArena[2][0] == player)) {
        return true;
    }

    return false;
}

void Game::resetGame() {
    board = GameBoard(board.getSize(), player1, player2); // Resetează tabla
    board.setFirstMove(true); // Resetează flag-ul de prima mutare

    // Reseteaza vrajitorii pentru un nou joc
    player1.resetWizardForGame();
    player2.resetWizardForGame();

    // Atribuie vrăjitori noi
    if (isWizardsDuel) {
        player1.setWizard(Wizard::getRandomWizard());
        player2.setWizard(Wizard::getRandomWizardDistinctFrom(player1.getWizard()));

        // Afișează informații despre vrăjitori
        std::cout << player1.getName() << " has been assigned the wizard: "
            << player1.getWizard().getName() << " with power "
            << player1.getWizard().getPower() << ".\n";

        std::cout << player2.getName() << " has been assigned the wizard: "
            << player2.getWizard().getName() << " with power "
            << player2.getWizard().getPower() << ".\n";
    }

    if (isElementalDuel) {
        std::cout << player1.getName() << " has been assigned the elemental power: "
            << player1.getElementalAbility() << ".\n";  // Corectat

        std::cout << player2.getName() << " has been assigned the elemental power: "
            << player2.getElementalAbility() << ".\n";  // Corectat
    }

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



int Game::validateRowInput(const std::string& prompt) {
    int row;
    while (true) {
        std::cout << prompt;
        std::cin >> row;
        if (!std::cin.fail() && row >= 0 && row < board.getSize()) {
            return row;
        }
        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::pair<int, int> Game::validateRowColInput(const std::string& prompt) {
    int row, col;
    while (true) {
        std::cout << prompt;
        std::cin >> row >> col;
        if (!std::cin.fail() && row >= 0 && row < board.getSize() && col >= 0 && col < board.getSize()) {
            return { row, col };
        }
        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool Game::useWizardAbility(Player& activePlayer, Player& opponent) {
    try {
        int row, col, destRow, destCol;

        switch (activePlayer.wizard.power) {
        case MagicPower::REMOVE_ROW_WITH_OWN_CARD:
            row = validateRowInput("Enter the row to remove: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, -1);
            return true;

        case MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN:
            std::tie(row, col) = validateRowColInput("Enter the row and column of the card to remove: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
            return true;

        case MagicPower::COVER_OPPONENT_CARD:
            std::tie(row, col) = validateRowColInput("Enter the row and column of the opponent's card to cover: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
            return true;

        case MagicPower::CREATE_HOLE:
            std::tie(row, col) = validateRowColInput("Enter the row and column of the empty space to transform into a hole: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
            return true;

        case MagicPower::MOVE_STACK_WITH_OWN_CARD:
            std::tie(row, col) = validateRowColInput("Enter the source row and column of the stack to move: ");
            std::tie(destRow, destCol) = validateRowColInput("Enter the destination row and column for the stack: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col, destRow, destCol);
            return true;

        case MagicPower::GAIN_EXTRA_CARD:
            std::tie(row, col) = validateRowColInput("Enter the row and column to place the Ether card: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col);
            return true;

        case MagicPower::MOVE_STACK_WITH_OPPONENT_CARD:
            std::tie(row, col) = validateRowColInput("Enter the source row and column of the opponent's stack to move: ");
            std::tie(destRow, destCol) = validateRowColInput("Enter the destination row and column for the stack: ");
            activePlayer.wizard.useAbility(board, activePlayer, opponent, row, col, destRow, destCol);
            return true;

        default:
            std::cout << "Invalid wizard ability.\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        return false;
    }
}

bool Game::useElementalPower(Player& user, Player& opponent) {
    if (!user.canUseElementalPower()) {
        std::cout << user.getName() << " cannot use an elemental power at the moment.\n";
        return false;
    }

    // Exemplu de utilizare a puterii: elimina o carte a oponentului
    // Puteți extinde această logică pentru fiecare tip de putere
    int row, col;
    std::cout << "Enter the row and column of the opponent’s card to affect: ";
    std::cin >> row >> col;

    if (!board.isValidPosition(row, col, 0)) {
        std::cout << "Invalid position. Elemental power failed.\n";
        return false;
    }

    if (board.isOccupiedBy(opponent, row, col)) {
        board.removeCard(row, col);
        user.usePower();  // Marchez puterea ca folosită
        std::cout << "Elemental power successfully used by " << user.getName() << ".\n";
        return true;
    }
    else {
        std::cout << "No opponent card at that position. Elemental power failed.\n";
        return false;
    }
}

void Game::calculateFinalScore() {
    int score1 = board.calculateScore(player1);
    int score2 = board.calculateScore(player2);

    std::cout << "\n==============================\n";
    std::cout << "        Final Scores          \n";
    std::cout << "==============================\n";
    std::cout << player1.getName() << ": " << score1 << " points\n";
    std::cout << player2.getName() << ": " << score2 << " points\n";

    if (score1 > score2) {
        std::cout << "\n🏆 " << player1.getName() << " wins the game! 🎉\n";
    }
    else if (score2 > score1) {
        std::cout << "\n🏆 " << player2.getName() << " wins the game! 🎉\n";
    }
    else {
        std::cout << "\n🤝 The game is a tie! 🏳️\n";
    }

    std::cout << "==============================\n";
}

void Game::startGame() {
    std::cout << "Game is resuming...\n";

    // Verifică dacă jocul a fost deja inițializat
    if (!player1.getHand().empty() && !player2.getHand().empty()) {
        std::cout << "[DEBUG] Hands already initialized. Skipping reset.\n";
    }
    else {
        std::cout << "Reinitializing hands for loaded game...\n";
        resetPlayerHand(player1);
        resetPlayerHand(player2);
    }

    board.printBoard();
    start(); // Pornește logica de joc
}


void Game::start() {
    while (true) {
        board.printBoard();
        Player& activePlayer = (currentPlayer == 1) ? player1 : player2;
        Player& opponent = (currentPlayer == 1) ? player2 : player1;

        std::string choice;

        // 🔹 Faza 1: Alegerea utilizării abilității vrăjitorului
        if (isWizardsDuel) {
            while (true) {
                std::cout << activePlayer.getName() << ", do you want to use your wizard's ability? (yes/no): ";
                std::cin >> choice;

                if (choice == "yes") {
                    if (activePlayer.wizard.usedThisMatch) {
                        std::cout << "The magical power has already been used this match!\n";
                    }
                    else {
                        try {
                            activePlayer.wizard.useAbility(board, activePlayer, opponent);
                            saveGameState();
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                            continue; // Sare la următorul tur
                        }
                        catch (const std::exception& e) {
                            std::cout << e.what() << "\n";
                        }
                    }
                }
                else if (choice == "no") {
                    break;
                }
                else {
                    std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
                }
            }
        }

        if (isElementalDuel) {
            while (true) {
                std::cout << activePlayer.getName() << ", do you want to use an elemental ability? (yes/no): ";
                std::cin >> choice;

                if (choice == "yes") {
                    if (activePlayer.usedElementalAbility) {
                        std::cout << "You have already used an elemental ability this round!\n";
                    }
                    else {
                        try {
                            activePlayer.useElementalAbility(board, activePlayer, opponent);
                            activePlayer.usedElementalAbility = true;
                            saveGameState();
                            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                            continue; // Sare la următorul tur
                        }
                        catch (const std::exception& e) {
                            std::cout << e.what() << "\n";
                        }
                    }
                }
                else if (choice == "no") {
                    break;
                }
                else {
                    std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
                }
            }
        }

        // 🔹 Faza 3: Alegerea plasării iluziilor sau a unei cărți normale
        while (true) {
            std::cout << activePlayer.getName() << ", do you want to place an illusion? (yes/no): ";
            std::cin >> choice;

            if (choice == "yes" && !activePlayer.hasPlacedIllusion) {
                if (placeIllusion(activePlayer, board)) {
                    activePlayer.hasPlacedIllusion = true; // Marchează că iluzia a fost folosită

                    saveGameState();  // Salvează după plasarea iluziilor

                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                    break; // Ieșim din acest while și continuăm la următoarea tură
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }
            else if (choice == "no") {
                if (placeNormalCard(activePlayer, board, opponent)) {
                    saveGameState();
                    // Verifică dacă explozia trebuie declanșată

                    if (board.canTriggerExplosion()) {
                        std::cout << activePlayer.getName() << ", do you want to trigger an explosion? (yes/no): ";
                        std::cin >> choice;
                        if (choice == "yes") {
                            board.triggerExplosion(activePlayer);
                            saveGameState();
                        }
                    }

                    // Verifică condiția de câștig
                    std::string winCondition = board.checkWinCondition(activePlayer);
                    if (!winCondition.empty()) {
                        std::cout << activePlayer.getName() << " wins by " << winCondition << "!\n";
                        return; // Termină jocul
                    }

                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Schimbă jucătorul
                    break; // Ieșim din while și continuăm jocul
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }
            else {
                std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
            }
        }
    }
    calculateFinalScore();
    return; // Termină jocul
}

bool Game::placeIllusion(Player& activePlayer, GameBoard& board) {
    if (activePlayer.hasPlacedIllusion) {
        std::cout << "[INFO] You have already placed an Illusion this game!\n";
        return false; // Jucătorul nu poate plasa altă iluzie
    }

    std::cout << "Select card index from hand (1-" << activePlayer.hand.size() << "): \n";

    int cardIndex;
    std::cin >> cardIndex;
    cardIndex -= 1; // Ajustare pentru vectorul intern

    if (cardIndex < 0 || cardIndex >= activePlayer.hand.size()) {
        std::cout << "[ERROR] Invalid card index!\n";
        return false;
    }

    // Obtine cartea selectata
    Card card = activePlayer.hand[cardIndex];

    if (card.isEther) {
        std::cout << "[ERROR] You cannot place the Ether card as an illusion!\n";
        return false;
    }

    // Alegerea poziției
    std::cout << activePlayer.getName() << "'s turn. Select row and column (e.g., 1 1): ";
    int row, col;
    std::cin >> row >> col;

    card.isIllusion = true;
    card.originalValue = card.value;

    if (board.placeIllusion(row, col, card, activePlayer)) {
        activePlayer.removeCard(cardIndex);
        activePlayer.hasPlacedIllusion = true;
        std::cout << "[SUCCESS] Illusion placed successfully at (" << row << ", " << col << ").\n";
        return true;
    }
    else {
        std::cout << "Invalid move. Cannot place an illusion there.\n";
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

        // **Verifică dacă explozia este posibilă**
        if (board.canTriggerExplosion()) {
            std::cout << activePlayer.getName() << ", do you want to trigger an explosion? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            if (choice == "yes") {
                board.triggerExplosion(activePlayer);
                std::cout << "[INFO] Explosion triggered successfully!\n";
            }
        }

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
