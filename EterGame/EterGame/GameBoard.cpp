//GameBoard.cpp

#include <queue>

#include "GameBoard.h"
#include "ExplosionPattern.h"

/// ================================
///     CONSTRUCTORI 
/// ================================

// Constructor principal
GameBoard::GameBoard(int size, Player& p1, Player& p2)
    : size(size),
    explosionOccurred(false),
    isFirstMove(true),
    board(size, std::vector<std::vector<std::optional<Card>>>(size, std::vector<std::optional<Card>>())),
    player1(&p1),
    player2(&p2) {
    std::cout << "Initialized board with size: " << size << "x" << size << "\n";
}

// Constructor secundar
GameBoard::GameBoard(int size)
    : size(size),
    explosionOccurred(false),
    isFirstMove(true),
    board(size, std::vector<std::vector<std::optional<Card>>>(size, std::vector<std::optional<Card>>())),
    player1(nullptr),
    player2(nullptr) {
    std::cout << "Initialized board with size: " << size << "x" << size << "\n";
}

/// ================================
/// 🔹 GETTERI ȘI SETTERI 🔹
/// ================================
int GameBoard::getSize() const {
    return size;
}

void GameBoard::setFirstMove(bool value)
{
    isFirstMove = value;
    // std::cout << "First move reset to: " << (isFirstMove ? "true" : "false") << "\n";
}

/// ================================
/// 🔹 VERIFICĂRI ȘI UTILITARE 🔹
/// ================================
bool GameBoard::isValidPosition(int row, int col, int depth) const {
    std::cout << "Validating position: (" << row << ", " << col << ", " << depth << ") for grid size: " << size << "\n";
    return row >= 0 && row < size && col >= 0 && col < size && depth >= 0;

    /*if (row < 0 || row >= size || col < 0 || col >= size) {
        std::cout << "Invalid row or column!\n";
        return false;
    }

    if (depth < 0) {
        std::cout << "Invalid depth!\n";
        return false;
    }

    return true;*/
}

bool GameBoard::isHole(int row, int col) const {
    return std::find(holes.begin(), holes.end(), std::make_pair(row, col)) != holes.end();
}

bool GameBoard::isSpaceEmpty(int row, int col) const
{
    return isValidPosition(row, col, 0) && board[row][col].empty();
}

bool GameBoard::isCardConnected(int row, int col) const {
    static const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];

        if (isValidPosition(newRow, newCol, 0) && !board[newRow][newCol].empty()) {
            return true;
        }
    }
    return false;
}

bool GameBoard::isOccupiedBy(const Player& player, int row, int col) const {
    if (!isValidPosition(row, col, 0) || board[row][col].empty()) {
        return false; // Invalid position or no card at that position.
    }
    //If not empty, check the owner of the top card
    return board[row][col].back()->owner == player.name;

}

/// =========================================
/// 🔹 GESTIONAREA PLASĂRII CĂRȚILOR 🔹
/// =========================================
bool GameBoard::placeCard(int row, int col, int depth, const Card& card, const Player& constPlayer) {
    std::cout << "[INFO] Attempting to place card at (" << row << ", " << col << ", " << depth << ")...\n";

    // Afișează starea grilei pentru debug
    std::cout << "[INFO] Grid size is: " << size << "x" << size << "\n";

    // Verifică validitatea poziției și adâncimii
    if (!isValidPosition(row, col, depth)) {
        std::cerr << "[ERROR] Invalid position: (" << row << ", " << col << ", " << depth << ").\n";
        return false;
    }

    // Verifică dacă poziția este marcată ca o groapă
    if (isHole(row, col)) {
        std::cerr << "[ERROR] Cannot place card on a hole at (" << row << ", " << col << ").\n";
        return false;
    }

    // Verifică regula adiacentă + Bypass regula adiacentului la prima mutare
    // Verifică regula adiacentă (prima mutare o ignoră)
    if (!isFirstMove && !hasAdjacentCard(row, col)) {
        std::cerr << "[ERROR] Cards must be placed adjacent to existing cards.\n";
        return false;
    }
    isFirstMove = false;

    // 🔹 Dacă la poziția respectivă există deja o carte
    if (!board[row][col].empty()) {
        Card& topCard = board[row][col].back().value();

        // Dacă cartea de deasupra este o iluzie, trebuie dezvăluită
        if (topCard.isIllusion) {
            std::cout << "[INFO] Revealing illusion at (" << row << ", " << col << ")!\n";
            topCard.isIllusion = false;  // Iluzia devine carte normală

            if (card.value > topCard.originalValue) {  // Doar o carte mai mare o poate înlocui
                std::cout << "[SUCCESS] Card " << card.value << " replaces the revealed illusion of value " << topCard.originalValue << ".\n";

                // 🔹 Actualizează owner-ul cărții care înlocuiește iluzia
                Card placedCard = card;
                placedCard.owner = constPlayer.name;
                board[row][col].push_back(placedCard);
                return true;
            }
            else {
                std::cerr << "[ERROR] Cannot place card with value " << card.value
                    << " over a revealed illusion with value " << topCard.originalValue << "!\n";
                return false;
            }
        }

        // 🔹 Regulă standard: o carte trebuie să fie mai mare decât cea de dedesubt
        if (card.value <= topCard.value) {
            std::cerr << "[ERROR] Cannot place a card with value less than or equal to the top card at this position.\n";
            return false;
        }
    }

    Card placedCard = card;
    placedCard.owner = constPlayer.name;
    board[row][col].push_back(placedCard);
    std::cout << "[DEBUG] Card placed: value " << placedCard.value
        << " | Owner: " << placedCard.owner
        << " at (" << row << ", " << col << ", " << depth << ")\n";
    return true;
}

bool GameBoard::isLineFull(int startRow, int startCol, int dRow, int dCol) const {
    std::cout << "[DEBUG] Checking if line is full starting at (" << startRow << ", " << startCol << ")\n";

    int depth = 0; // Asumare nivel implicit
    for (int i = 0; i < size; ++i) {
        int row = startRow + i * dRow;
        int col = startCol + i * dCol;

        if (!isValidPosition(row, col, 0)) {
            std::cout << "[DEBUG] Invalid position detected: (" << row << ", " << col << ")\n";
            return false;
        }

        if (board[row][col].empty()) {
            std::cout << "[DEBUG] Line is NOT full, missing at (" << row << ", " << col << ")\n";
            return false;
        }

        if (!board[row][col][0].has_value()) {
            std::cout << "[DEBUG] No card at (" << row << ", " << col << ")\n";
            return false;
        }
    }
    std::cout << "[DEBUG] Line is full!\n";
    return true;
}

void GameBoard::removeCard(int x, int y) {
    if (!board[x][y].empty() && board[x][y].back().has_value()) {
        board[x][y].pop_back(); // Elimină cartea de deasupra teancului
        std::cout << "[SUCCESS] Card removed at (" << x << ", " << y << ").\n";
    }
}

void GameBoard::returnCardToPlayer(int x, int y) {
    if (!board[x][y].empty() && board[x][y].back().has_value()) {
        Player* owner = nullptr;

        // Determină proprietarul cărții
        if (board[x][y].back()->owner == player1->name) {
            owner = player1;
        }
        else if (board[x][y].back()->owner == player2->name) {
            owner = player2;
        }

        if (owner) {
            owner->addCard(board[x][y].back().value()); // Adaugă cartea înapoi în mână
            board[x][y].pop_back(); // Elimină cartea de pe tablă
            std::cout << "Card returned to " << owner->getName() << " from (" << x << ", " << y << ").\n";
        }
    }
}

/// ===================================================
/// 🔹 REGULI SPECIALE (ILUZII, GROPI, EXPLOZII) 🔹
/// ===================================================
bool GameBoard::createHole(int row, int col) {
    if (!isValidPosition(row, col, 0)) {
        std::cerr << "[ERROR] Invalid position for hole creation: (" << row << ", " << col << ").\n";
        return false;
    }

    if (isHole(row, col)) {
        std::cerr << "[ERROR] A hole already exists at (" << row << ", " << col << ").\n";
        return false;
    }

    holes.emplace_back(row, col);
    std::cout << "[SUCCESS] Hole created at (" << row << ", " << col << ").\n";
    return true;
}

bool GameBoard::placeIllusion(int row, int col, Card card, Player& player) {
    std::cout << "[INFO] Attempting to place an illusion at (" << row << ", " << col << ")...\n";

    if (!isValidPosition(row, col, 0)) {
        std::cerr << "[ERROR] Invalid position for illusion!\n";
        return false;
    }

    if (!board[row][col].empty()) {
        std::cerr << "[ERROR] Cannot place an illusion over another card!\n";
        return false;
    }

    std::cout << "[DEBUG] Iluzia a fost plasată corect!\n";

    card.isIllusion = true;
    card.owner = player.name;
    //card.value = -1;
    board[row][col].push_back(card);
    player.hasPlacedIllusion = true; // Marchează că jucătorul a folosit iluzia

    std::cout << "[SUCCESS] Illusion placed at (" << row << ", " << col << ") by " << player.getName() << ".\n";
    return true;
}

bool GameBoard::revealIllusion(int row, int col, int depth, Player& opponent) {
    if (depth < 0 || depth >= board[row][col].size() || !board[row][col][depth].has_value()) {
        std::cerr << "[ERROR] No valid illusion found at (" << row << ", " << col << ", " << depth << ").\n";
        return false;
    }

    Card& illusion = board[row][col][depth].value(); // Obtine iluzia
    if (!illusion.isIllusion) {
        std::cerr << "[ERROR] Card at (" << row << ", " << col << ") is not an illusion.\n";
        return false;
    }

    // * Dezvăluie iluzia și setează valoarea originală
    std::cout << "[INFO] Revealing illusion at (" << row << ", " << col << ")! Original value: " << illusion.originalValue << "\n";
    board[row][col].pop_back();

    // * Selectează o carte din mâna adversarului pentru a acoperi iluzia
    std::cout << opponent.getName() << ", select a card from your hand to cover the illusion: ";
    int cardIndex;
    std::cin >> cardIndex;
    cardIndex -= 1; // Ajustare index

    if (cardIndex < 0 || cardIndex >= opponent.hand.size()) {
        std::cerr << "[ERROR] Invalid card selection.\n";
        return false;
    }

    Card opponentCard = opponent.hand[cardIndex];

    // Setează corect proprietarul cărți
    opponentCard.owner = opponent.name;

    if (opponentCard.value > illusion.originalValue) {
        std::cout << "[SUCCESS] Card " << opponentCard.value << " replaces the revealed illusion of value " << illusion.originalValue << ".\n";

        // Elimină orice carte veche și pune cartea nouă cu proprietarul corect
        board[row][col].push_back(std::optional<Card>(opponentCard));

        // Elimină cartea din mâna adversarului
        opponent.removeCard(cardIndex);

        // Verifică condiția de câștig după înlocuire
        std::string winCondition = checkWinCondition(opponent);
        if (!winCondition.empty()) {
            std::cout << "[WIN] " << opponent.getName() << " wins with " << winCondition << "!\n";
            return true;
        }
    }
    else {
        std::cout << "[INFO] Opponent's card was too weak! Losing turn and removing the card from play.\n";
        opponent.removeCard(cardIndex);
        return false; // Nu s-a putut acoperi iluzia
    }

    return true;
}

bool GameBoard::canTriggerExplosion() const {
    int fullLines = 0;
    for (int i = 0; i < size; ++i) {
        if (isLineFull(i, 0, 0, 1)) ++fullLines;
        if (isLineFull(0, i, 1, 0)) ++fullLines;
    }
    return fullLines >= 2;
}

bool GameBoard::triggerExplosion(Player& currentPlayer) {
    int lastMoveRow = 0; // Exemplu, setează ultima mutare reală
    int lastMoveCol = 0;

    if (explosionOccurred) {
        std::cerr << "[ERROR] Explosion has already occurred. No further explosions can happen.\n";
        return false;
    }

    std::cout << "[SUCCESS] Explosion triggered by " << currentPlayer.getName() << "!\n";
    explosionOccurred = true;

    ExplosionPattern explosion(size);
    explosion.applyExplosion(*this, lastMoveRow, lastMoveCol);

    // Verifică dacă explozia ar rupe conexiunea tablei
    validateBoardIntegrity();
}

void GameBoard::applyExplosion(const ExplosionPattern& explosion) {
    std::cout << "[INFO] Applying explosion effects...\n";

    for (const auto& tile : explosion.getTiles()) {
        if (!isValidPosition(tile.x, tile.y, 0)) {
            std::cerr << "[ERROR] Invalid position for explosion effect at (" << tile.x << ", " << tile.y << ").\n";
            continue;
        }

        switch (tile.effect) {
        case ExplosionEffect::RemoveCard:
            std::cout << "[ACTION] Removing card at (" << tile.x << ", " << tile.y << ").\n";
            removeCard(tile.x, tile.y);
            break;

        case ExplosionEffect::ReturnToHand:
            std::cout << "[ACTION] Returning card to player from (" << tile.x << ", " << tile.y << ").\n";
            returnCardToPlayer(tile.x, tile.y);
            break;

        case ExplosionEffect::CreateHole:
            if (createHole(tile.x, tile.y)) {
                std::cout << "[ACTION] Hole created at (" << tile.x << ", " << tile.y << ").\n";
            }
            else {
                std::cerr << "[WARNING] Failed to create hole at (" << tile.x << ", " << tile.y << ").\n";
            }
            break;
        }
    }

    std::cout << "[INFO] Explosion effects applied successfully.\n";
}

void GameBoard::validateBoardIntegrity() {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (!isCardConnected(row, col)) {
                std::cout << "[WARNING] Explosion effect ignored at (" << row << ", " << col << ") to maintain connectivity.\n";
            }
        }
    }
}

/// ================================
/// 🔹 SISTEMUL DE SCOR ȘI CONDIȚIILE DE CÂȘTIG 🔹
/// ================================
std::string GameBoard::checkWinCondition(const Player& player) const {
    // Verificare linii orizontale
    for (int row = 0; row < size; ++row) {
        bool horizontalWin = true;
        for (int col = 0; col < size; ++col) {
            if (board[row][col].empty() ||
                !board[row][col][0].has_value() ||
                board[row][col][0]->isIllusion || // Ignoră iluziile
                board[row][col][0]->owner != player.name)
            {
                horizontalWin = false;
                std::cout << "Debug: Position (" << row << ", " << col << ") breaks horizontal condition. "
                    << "Owner: " << (board[row][col].empty() ? "empty" : board[row][col][0]->owner) << "\n";
                break;
            }
        }
        if (horizontalWin) {
            std::cout << "[WIN] " << player.getName() << " wins with a horizontal line at row " << row << "!\n";
            return "Horizontal line at row " + std::to_string(row);
        }
    }

    // Verificare coloane verticale
    for (int col = 0; col < size; ++col) {
        bool verticalWin = true;
        for (int row = 0; row < size; ++row) {
            if (board[row][col].empty() ||
                !board[row][col][0].has_value() ||
                board[row][col][0]->isIllusion || // Ignoră iluziile
                board[row][col][0]->owner != player.name)
            {
                verticalWin = false;
                std::cout << "Debug: Position (" << row << ", " << col << ") breaks vertical condition. "
                    << "Owner: " << (board[row][col].empty() ? "empty" : board[row][col][0]->owner) << "\n";
                break;
            }
        }
        if (verticalWin) {
            std::cout << "[WIN] " << player.getName() << " wins with a vertical line at column " << col << "!\n";
            return "Vertical line at column " + std::to_string(col);
        }
    }

    // Verificare diagonală principală (\)
    bool diagonalWin1 = true;
    for (int d = 0; d < size; ++d) {
        if (board[d][d].empty() ||
            !board[d][d][0].has_value() ||
            board[d][d][0]->isIllusion || // Ignoră iluziile
            board[d][d][0]->owner != player.name)
        {
            diagonalWin1 = false;
            std::cout << "Debug: Position (" << d << ", " << d << ") breaks main diagonal condition.\n";
            break;
        }
    }
    if (diagonalWin1) {
        std::cout << "[WIN] " << player.getName() << " wins with a main diagonal line!\n";
        return "Main diagonal (\\)";
    }

    // Verificare diagonală secundară (/)
    bool diagonalWin2 = true;
    for (int d = 0; d < size; ++d) {
        if (board[d][size - 1 - d].empty() ||
            !board[d][size - 1 - d][0].has_value() ||
            board[d][size - 1 - d][0]->isIllusion || // Ignoră iluziile
            board[d][size - 1 - d][0]->owner != player.name)
        {
            diagonalWin2 = false;
            std::cout << "Debug: Position (" << d << ", " << size - 1 - d << ") breaks secondary diagonal condition.\n";
            break;
        }
    }
    if (diagonalWin2) {
        std::cout << "[WIN] " << player.getName() << " wins with a secondary diagonal line!\n";
        return "Secondary diagonal (/)";
    }

    // Dacă nu există o condiție de câștig
    std::cout << "Debug: No win condition detected for player " << player.name << "\n";
    return "";
}

int GameBoard::calculateScore(const Player& player) const {
    int score = 0;

    // Iterează prin fiecare poziție de pe tablă
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            // Iterează prin toate nivelurile de la poziția (row, col)
            for (const auto& card : board[row][col]) {
                if (card.has_value() && card->owner == player.name) {
                    // Adaugă valoarea cărții la scor
                    score += card->isIllusion ? 1 : card->value;
                }
            }
        }
    }

    return score;
}

/// ================================
/// 🔹 AFIȘAREA TABLEI DE JOC 🔹
/// ================================
void GameBoard::printBoard() const {
    std::cout << "\nCurrent Board State:\n";

    // Etichetele coloanelor
    std::cout << "    ";
    for (int col = 0; col < size; ++col) {
        std::cout << col << "   |  \b";
        /// "\b" este un caracter backspace pentru a șterge un spațiu în plus
    }
    std::cout << "\n";

    // Linie separatoare
    std::cout << "--" << std::string(size * 6, '-') << "|\n";

    // Iteram prin rânduri si coloane
    for (int row = 0; row < size; ++row) {
        std::cout << row << " | "; // Eticheta rândului

        for (int col = 0; col < size; ++col) {
            if (isHole(row, col)) {
                std::cout << "H. | "; // Marcaj pentru gropi
            }
            else if (!board[row][col].empty()) {
                const Card& card = board[row][col].back().value();
                char ownerSymbol = '.';

                // 🔹 Determină proprietarul corect
                if (!card.owner.empty()) {
                    if (player1 && card.owner == player1->name) {
                        ownerSymbol = 'a';
                    }
                    else if (player2 && card.owner == player2->name) {
                        ownerSymbol = 'b';
                    }
                }

                // 🔹 Afișează corect iluziile și cărțile normale
                if (card.isIllusion) {
                    std::cout << "?   | ";  // Iluziile sunt reprezentate ca "?"
                }
                else {
                    std::cout << card.value << ownerSymbol << "  | ";
                }
            }
            else {
                std::cout << "..  | "; // Poziție goală
            }
        }
        std::cout << "\n";
    }

    // Linie separatoare între rânduri
    std::cout << "--" << std::string(size * 6, '-') << "|\n";
}

bool GameBoard::hasAdjacentCard(int row, int col) const {
    std::cout << "Checking adjacency for position (" << row << ", " << col << ")...\n";
    static const int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (isValidPosition(newRow, newCol, 0) && !board[newRow][newCol].empty()) {
            return true;
        }
    }
    return false;
}

bool GameBoard::checkIllusionRule(int row, int col, Player& opponent) {
    // Verifică dacă poziția este validă
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Invalid position on the board!");
    }

    // Verifică dacă există o carte la poziția specificată
    if (board[row][col].empty() || !board[row][col].back().has_value()) {
        throw std::runtime_error("No card exists at the given position!");
    }

    // Obține referința la cartea de deasupra
    auto& placedCard = board[row][col].back().value();

    // Verifică dacă este o carte "Illusion"
    if (!placedCard.isIllusion) {
        return false; // Nu este o iluzie
    }

    // Dezvăluie iluzia și aplică regulile specifice
    std::cout << "Illusion revealed at (" << row << ", " << col << ")!\n";
    placedCard.isIllusion = false; // Iluzia devine o carte normală

    // Interacțiunea cu oponentul
    if (!opponent.hand.empty()) {
        // Găsește o carte din mâna oponentului
        int cardIndex;
        std::cout << "Select a card from your hand to attempt covering the illusion (1-"
            << opponent.hand.size() << "): ";
        std::cin >> cardIndex;
        cardIndex -= 1; // Ajustează indexul pentru vector

        if (cardIndex < 0 || cardIndex >= opponent.hand.size()) {
            throw std::runtime_error("Invalid card index!");
        }

        const Card& opponentCard = opponent.hand[cardIndex];

        // Regula: Dacă valoarea cărții oponentului este mai mică sau egală cu valoarea iluziei
        if (opponentCard.value <= placedCard.value) {
            // Cartea oponentului este eliminată
            std::cout << "Opponent's card (value " << opponentCard.value
                << ") is eliminated!\n";
            opponent.removeCard(cardIndex); // Elimină cartea din mână
            return true; // Oponentul își încheie tura
        }
        else {
            // Cartea oponentului acoperă iluzia
            std::cout << "Opponent successfully covered the illusion with card of value "
                << opponentCard.value << ".\n";
            board[row][col].emplace_back(opponentCard); // Plasează cartea oponentului pe tablă
            opponent.removeCard(cardIndex); // Elimină cartea din mână
        }
    }

    return true; // Oponentul a interacționat cu iluzia
}

/*
 * Elimină o carte a adversarului de pe tablă care acoperă o carte proprie
 */
void GameBoard::removeOpponentCardOverOwn(int row, int col, const Player& currentPlayer) {
    // Verifică dacă poziția este validă
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Invalid position on the board!");
    }

    // Verifică dacă poziția are cărți
    if (board[row][col].empty()) {
        throw std::runtime_error("No cards at the given position to remove!");
    }

    // Verifică dacă ultima carte de pe teanc este a oponentului
    const Card& topCard = board[row][col].back().value();
    if (topCard.owner == currentPlayer.name) {
        throw std::runtime_error("Cannot remove your own card!");
    }

    // Verifică dacă există o carte proprie dedesubt
    bool hasOwnCardBelow = false;
    for (size_t depth = 0; depth < board[row][col].size() - 1; ++depth) {
        if (board[row][col][depth].has_value() && board[row][col][depth]->owner == currentPlayer.name) {
            hasOwnCardBelow = true;
            break;
        }
    }

    if (!hasOwnCardBelow) {
        throw std::runtime_error("No own card below the opponent's card!");
    }

    // Elimină cartea adversarului
    board[row][col].pop_back();
    std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
}

/*
 * Elimină un întreg rând de cărți de pe tablă.
 * Rândul trebuie să ocupe cel puțin 3 poziții și să conțină cel puțin o carte proprie vizibilă.
 * Se elimină teancurile, nu numai cărțile de deasupra.
 */
void GameBoard::removeRowWithOwnCard(int row, const Player& currentPlayer) {
    // Verifică dacă rândul este valid
    if (row < 0 || row >= size) {
        throw std::out_of_range("Invalid row index!");
    }

    // Verifică dacă rândul îndeplinește condițiile
    int occupiedPositions = 0;
    bool hasOwnCard = false;

    for (int col = 0; col < size; ++col) {
        if (!board[row][col].empty()) {
            ++occupiedPositions;
            // Verifică dacă există o carte a jucătorului curent la această poziție
            for (const auto& card : board[row][col]) {
                if (card.has_value() && card->owner == currentPlayer.name) {
                    hasOwnCard = true;
                    break;
                }
            }
        }
    }

    // Condiții: minim 3 poziții ocupate și cel puțin o carte proprie
    if (occupiedPositions < 3) {
        throw std::runtime_error("The row must occupy at least 3 positions!");
    }
    if (!hasOwnCard) {
        throw std::runtime_error("The row must contain at least one of your cards!");
    }

    // Elimină toate cărțile din rând
    for (int col = 0; col < size; ++col) {
        if (!board[row][col].empty()) {
            board[row][col].clear(); // Șterge toate nivelurile
        }
    }

    std::cout << "Removed all cards from row " << row << ".\n";
}
/*
 * Acoperă o carte a oponentului cu o carte proprie de valoare strict mai mică din mână.
 */
void GameBoard::coverOpponentCard(int row, int col, Player& currentPlayer) {
    // Verifică dacă poziția este validă
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Invalid position on the board!");
    }

    // Verifică dacă există un teanc de cărți la poziția specificată
    if (board[row][col].empty()) {
        throw std::runtime_error("No stack exists at the given position!");
    }

    // Obține cartea de deasupra
    const Card& topCard = board[row][col].back().value();

    // Verifică dacă cartea de deasupra aparține adversarului
    if (topCard.owner == currentPlayer.name) {
        throw std::runtime_error("You cannot cover your own card!");
    }

    // Găsește o carte din mâna jucătorului curent care are valoarea mai mică decât cea a cărții de deasupra
    auto it = std::find_if(currentPlayer.hand.begin(), currentPlayer.hand.end(),
        [&](const Card& card) {
            return card.value < topCard.value && !card.isIllusion; // Trebuie să fie mai mică și să nu fie o iluzie
        });

    // Dacă nu există o astfel de carte, aruncă o excepție
    if (it == currentPlayer.hand.end()) {
        throw std::runtime_error("No valid card in hand to cover the opponent's card!");
    }

    // Plasează cartea jucătorului curent peste teanc
    board[row][col].emplace_back(*it);

    // Elimină cartea din mâna jucătorului curent
    currentPlayer.hand.erase(it);

    std::cout << "Covered opponent's card at (" << row << ", " << col
        << ") with your card of value " << board[row][col].back()->value << ".\n";
}

/*
 * Mută un teanc de cărți cu propria carte deasupra pe o altă poziție goală pe tablă.
*/
void GameBoard::moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer) {
    // Verifică dacă pozițiile sunt valide
    if (srcRow < 0 || srcRow >= size || srcCol < 0 || srcCol >= size ||
        destRow < 0 || destRow >= size || destCol < 0 || destCol >= size) {
        throw std::out_of_range("Invalid source or destination position!");
    }

    // Verifică dacă sursa conține un teanc de cărți
    if (board[srcRow][srcCol].empty()) {
        throw std::runtime_error("No stack exists at the source position!");
    }

    // Verifică dacă poziția țintă este goală
    if (!board[destRow][destCol].empty()) {
        throw std::runtime_error("The destination position is not empty!");
    }

    // Verifică dacă ultima carte din teancul sursă aparține jucătorului curent
    const Card& topCard = board[srcRow][srcCol].back().value();
    if (topCard.owner != currentPlayer.name) {
        throw std::runtime_error("You can only move stacks where your card is on top!");
    }

    // Mută teancul
    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    board[srcRow][srcCol].clear();

    std::cout << "Moved stack from (" << srcRow << ", " << srcCol << ") to ("
        << destRow << ", " << destCol << ").\n";
}

/*
 * Capătă o extra carte Eter care se plasează imediat pe tablă.
 */
void GameBoard::placeEtherCard(int row, int col, const Player& currentPlayer) {
    // Verifică dacă poziția este validă
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Invalid position on the board!");
    }

    // Verifică dacă poziția este marcată ca o groapă
    if (isHole(row, col)) {
        throw std::runtime_error("Cannot place Ether card on a hole!");
    }

    // Verifică dacă poziția este goală
    if (!board[row][col].empty()) {
        throw std::runtime_error("Cannot place Ether card on a non-empty position!");
    }

    // Plasează cartea Ether pe poziția specificată
    board[row][col].emplace_back(Card(0, false, true, currentPlayer.name));

    std::cout << "Placed Ether card at (" << row << ", " << col << ") for "
        << currentPlayer.name << ".\n";
}

/*
 * Mută un teanc de cărți cu cartea adversarului deasupra pe o altă poziție goală pe tablă.
 */
void GameBoard::moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer) {
    // Verifică dacă pozițiile sunt valide
    if (srcRow < 0 || srcRow >= size || srcCol < 0 || srcCol >= size ||
        destRow < 0 || destRow >= size || destCol < 0 || destCol >= size) {
        throw std::out_of_range("Invalid source or destination position!");
    }

    // Verifică dacă sursa conține un teanc de cărți
    if (board[srcRow][srcCol].empty()) {
        throw std::runtime_error("No stack exists at the source position!");
    }

    // Verifică dacă poziția țintă este goală
    if (!board[destRow][destCol].empty()) {
        throw std::runtime_error("The destination position is not empty!");
    }

    // Obține cartea de deasupra teancului de la poziția sursă
    const Card& topCard = board[srcRow][srcCol].back().value();

    // Verifică dacă ultima carte din teanc aparține adversarului
    if (topCard.owner == currentPlayer.name) {
        throw std::runtime_error("You can only move stacks with the opponent's card on top!");
    }

    // Mută teancul
    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    board[srcRow][srcCol].clear();

    std::cout << "Moved stack with opponent's card from (" << srcRow << ", " << srcCol
        << ") to (" << destRow << ", " << destCol << ").\n";
}

/*
 *Mută oricare rând aflat la “marginea” tablei pe o altă “margine”. Rândul mutat trebuie să ocupe cel puțin 3 poziții.
*/
void GameBoard::moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol) {
    // Verifică dacă pozițiile sursă și destinație sunt pe marginea tablei
    if (!((srcRow == 0 || srcRow == size - 1 || srcCol == 0 || srcCol == size - 1) &&
        (destRow == 0 || destRow == size - 1 || destCol == 0 || destCol == size - 1))) {
        throw std::runtime_error("Source and destination must be on the edges of the board!");
    }

    // Verifică dacă rândul sau coloana sursă este validă
    int occupiedPositions = 0;
    if (srcRow == 0 || srcRow == size - 1) { // Mutare pe orizontală
        for (int col = 0; col < size; ++col) {
            if (!board[srcRow][col].empty()) {
                ++occupiedPositions;
            }
        }
    }
    else if (srcCol == 0 || srcCol == size - 1) { // Mutare pe verticală
        for (int row = 0; row < size; ++row) {
            if (!board[row][srcCol].empty()) {
                ++occupiedPositions;
            }
        }
    }
    else {
        throw std::runtime_error("Invalid source row/column!");
    }

    // Verifică dacă sursa conține cel puțin 3 poziții ocupate
    if (occupiedPositions < 3) {
        throw std::runtime_error("The source row/column must occupy at least 3 positions!");
    }

    // Verifică dacă destinația este complet goală
    if (destRow == 0 || destRow == size - 1) { // Mutare pe orizontală
        for (int col = 0; col < size; ++col) {
            if (!board[destRow][col].empty()) {
                throw std::runtime_error("Destination row is not empty!");
            }
        }
    }
    else if (destCol == 0 || destCol == size - 1) { // Mutare pe verticală
        for (int row = 0; row < size; ++row) {
            if (!board[row][destCol].empty()) {
                throw std::runtime_error("Destination column is not empty!");
            }
        }
    }
    else {
        throw std::runtime_error("Invalid destination row/column!");
    }

    // Mută rândul sau coloana
    if (srcRow == 0 || srcRow == size - 1) { // Mutare pe orizontală
        for (int col = 0; col < size; ++col) {
            board[destRow][col] = std::move(board[srcRow][col]);
            board[srcRow][col].clear();
        }
    }
    else if (srcCol == 0 || srcCol == size - 1) { // Mutare pe verticală
        for (int row = 0; row < size; ++row) {
            board[row][destCol] = std::move(board[row][srcCol]);
            board[row][srcCol].clear();
        }
    }

    std::cout << "Moved row/column from edge (" << srcRow << ", " << srcCol
        << ") to edge (" << destRow << ", " << destCol << ").\n";
}



