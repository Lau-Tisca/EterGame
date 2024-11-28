#include "Wizard.h"
#include <iostream>

Wizard::Wizard(const std::u8string& name, const std::u8string& power)
    : m_name(name), m_power(power), m_powerUsed(false) {}

// Getteri
std::u8string Wizard::getName() const {
    return m_name;
}

std::u8string Wizard::getPowerName() const {
    return m_power;
}

// puterile
void Wizard::useAbility(GameBoard& board, int row, int col, Player& currentPlayer, int destRow, int destCol) {
    if (usedThisMatch) {
        throw std::runtime_error("The magical power has already been used this match!");
    }
    if (usedThisGame) {
        throw std::runtime_error("The magical power has already been used this game!");
    }

    usedThisGame = true;
    usedThisMatch = true;

    switch (power) {
    case MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN:
        board.removeOpponentCardOverOwn(row, col, currentPlayer);
        break;
    case MagicPower::REMOVE_ROW_WITH_OWN_CARD:
        board.removeRowWithOwnCard(row, currentPlayer);
    case MagicPower::COVER_OPPONENT_CARD:
        board.coverOpponentCard(row, col, currentPlayer);
    case MagicPower::CREATE_HOLE:
        board.createHole(row, col);
    case MagicPower::MOVE_STACK_WITH_OWN_CARD:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination row and column must be specified for this ability!");
        }
        board.moveStackWithOwnCard(row, col, destRow, destCol, currentPlayer);
    case MagicPower::GAIN_EXTRA_CARD: {
        board.placeEtherCard(row, col, currentPlayer);
    case MagicPower::MOVE_STACK_WITH_OPPONENT_CARD:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination row and column must be specified for this ability!");
        }
        board.moveStackWithOpponentCard(row, col, destRow, destCol, currentPlayer);
    case MagicPower::MOVE_ROW_TO_EDGE:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination edge must be specified for this ability!");
        }
        board.moveRowToEdge(row, col, destRow, destCol);
        break;
    }
                                    break;
    default:
        throw std::runtime_error("Invalid magical power!");
    }

    std::cout << name << " used their magical power!\n";
}

bool Wizard::usePower(Board& board, Player& currentPlayer, Player& opponent) {
    if (m_powerUsed) {
        std::cout << "Puterea vrăjitorului " << std::string(m_name.begin(), m_name.end()) << " a fost deja utilizată!" << std::endl;
        return false;
    }

    std::string convertedPower(m_power.begin(), m_power.end());
    std::string convertedName(m_name.begin(), m_name.end());
    //explozie
    if (convertedPower == "Explosion") {
        // Exemplu: Șterge toate cărțile dintr-un rând
        int row = 0;  // Aici poți primi input pentru a alege rândul
        for (auto& cell : board.getLine(row)) {
            while (!cell.empty()){
                cell.pop();
        }
        std::cout << "Explozie activată de " << convertedName << "!" << std::endl;
    }

    //ilussion
    else if (convertedPower == "Illusion") {
        // Iluzie: Plasează o carte falsă
        int row, col;
        std::cout << "Alege poziția pentru cartea falsă (rând coloană): ";
        std::cin >> row >> col;

        if (board.isPositionValid(row, col)) {
            board.placeIllusion(row, col);  // Metodă în Board pentru plasarea unei iluzii
            std::cout << convertedName << " a plasat o carte falsă la (" << row << ", " << col << ")!" << std::endl;
        }
        else {
            std::cout << "Poziție invalidă!" << std::endl;
            return false;
        }
    }

    else if (convertedPower == "Freeze") {
        // Freeze: Blochează o poziție
        int row, col;
        std::cout << "Alege poziția pentru a fi înghețată (rând coloană): ";
        std::cin >> row >> col;

        if (board.isPositionValid(row, col)) {
            board.freezeCell(row, col);  // Metodă în Board pentru înghețare
            std::cout << convertedName << " a înghețat poziția (" << row << ", " << col << ")!" << std::endl;
        }
        else {
            std::cout << "Poziție invalidă!" << std::endl;
            return false;
        }
    }

    else if (convertedPower == "Steal") {
        // Steal: Fură o carte din mâna adversarului
        if (opponent.getDeckSize() > 0) {
            int index;
            std::cout << "Alege indexul cărții pe care vrei să o furi (0-" << opponent.getDeckSize() - 1 << "): ";
            std::cin >> index;

            if (index >= 0 && index < opponent.getDeckSize()) {
                auto stolenCard = opponent.removeCard(index);  // Elimină cartea din mâna adversarului
                currentPlayer.addCard(stolenCard);  // Adaugă cartea în mâna jucătorului curent
                std::cout << convertedName << " a furat o carte!" << std::endl;
            }
            else {
                std::cout << "Index invalid!" << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Adversarul nu are cărți de furat!" << std::endl;
            return false;
        }

    m_powerUsed = true;  // Marchez că puterea a fost utilizată
    return true;


}

    else if(convertedPower == "RemoveStackCoveringOwnCard") {
        // Elimină o carte a adversarului care acoperă o carte proprie
        int row, col;
        std::cout << "Alege poziția de unde să elimini teancul (rând coloană): ";
        std::cin >> row >> col;

        if (board.hasOwnCardBelow(row, col, currentPlayer)) { //trebuie implementate in board functiile hasOwnCardBelow si RemoveStack
            board.removeStack(row, col);
            std::cout << "Teancul de la (" << row << ", " << col << ") a fost eliminat!" << std::endl;
        }
        else {
            std::cout << "Nu există o carte proprie dedesubt la poziția aleasă!" << std::endl;
            return false;
        }
    }
    else if (convertedPower == "RemoveRowWithOwnCard") {
        // Elimină un întreg rând care conține cel puțin 3 poziții și o carte proprie vizibilă
        int row;
        std::cout << "Alege rândul pentru eliminare: ";
        std::cin >> row;

        if (board.isValidRowForRemoval(row, currentPlayer)) { //trebuie implementate functiile in board
            board.removeRow(row);
            std::cout << "Rândul " << row << " a fost eliminat!" << std::endl;
        }
        else {
            std::cout << "Rândul ales nu îndeplinește condițiile pentru eliminare!" << std::endl;
            return false;
        }

    }
    else if (convertedPower == "CoverOpponentCard") {
        // Acoperă o carte a oponentului cu o carte proprie de valoare strict mai mică
        int row, col, cardIndex;
        std::cout << "Alege poziția adversarului (rând coloană) și cartea din mână: ";
        std::cin >> row >> col >> cardIndex;

        if (currentPlayer.hasCard(cardIndex) && board.isOpponentCardOnTop(row, col, opponent)) {
            auto selectedCard = currentPlayer.getCard(cardIndex);
            if (selectedCard.getValue() < board.getTopCard(row, col).getValue()) {
                board.placeCard(row, col, selectedCard);
                currentPlayer.removeCard(cardIndex);
                std::cout << "Cartea a fost plasată peste adversar la (" << row << ", " << col << ")." << std::endl;
            }
            else {
                std::cout << "Cartea selectată nu are o valoare strict mai mică decât cea a adversarului!" << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Poziția sau cartea aleasă nu este validă!" << std::endl;
            return false;
        }
    }
    else if (convertedPower == "CreatePit") {
        // Transformă un spațiu gol într-o groapă
        int row, col;
        std::cout << "Alege poziția pentru a crea o groapă (rând coloană): ";
        std::cin >> row >> col;

        if (board.isPositionEmpty(row, col)) {
            board.createPit(row, col);
            std::cout << "Groapa a fost creată la (" << row << ", " << col << ")." << std::endl;
        }
        else {
            std::cout << "Poziția aleasă nu este goală!" << std::endl;
            return false;
        }
        }
    else if (convertedPower == "MoveOwnStack") {
            // Mută un teanc cu o carte proprie deasupra pe o altă poziție goală
            int fromRow, fromCol, toRow, toCol;
            std::cout << "Alege poziția teancului propriu (rând coloană) și poziția de destinație (rând coloană): ";
            std::cin >> fromRow >> fromCol >> toRow >> toCol;

            if (board.canMoveOwnStack(fromRow, fromCol, toRow, toCol, currentPlayer)) {
                board.moveStack(fromRow, fromCol, toRow, toCol);
                std::cout << "Teancul a fost mutat la (" << toRow << ", " << toCol << ")." << std::endl;
            }
            else {
                std::cout << "Mutarea nu este validă!" << std::endl;
                return false;
            }
            }
    else if (m_power == "ExtraEterCard") {
        // Capătă o carte Eter suplimentară și o plasează imediat
        int row, col;
        std::cout << "Alege poziția pentru a plasa cartea Eter: ";
        std::cin >> row >> col;

        if (board.isPositionEmpty(row, col)) {
            auto eterCard = currentPlayer.getExtraEterCard();
            board.placeCard(row, col, eterCard);
            std::cout << "Cartea Eter a fost plasată la (" << row << ", " << col << ")." << std::endl;
        }
        else {
            std::cout << "Poziția aleasă nu este goală!" << std::endl;
            return false;
        }
        }

    else if (m_power == "MoveOpponentStack") {
        // Mută un teanc de cărți cu cartea adversarului deasupra pe o altă poziție goală
        int fromRow, fromCol, toRow, toCol;
        std::cout << "Alege poziția teancului adversarului (rând coloană) și poziția de destinație (rând coloană): ";
        std::cin >> fromRow >> fromCol >> toRow >> toCol;

        if (board.canMoveOpponentStack(fromRow, fromCol, toRow, toCol, opponent)) {
            board.moveStack(fromRow, fromCol, toRow, toCol);
            std::cout << "Teancul adversarului a fost mutat la (" << toRow << ", " << toCol << ")." << std::endl;
        }
        else {
            std::cout << "Mutarea nu este validă!" << std::endl;
            return false;
        }
        }
    else if (m_power == "MoveEdgeRow") {
        // Mută un rând de la marginea tablei pe o altă margine
        int fromEdge, toEdge;
        std::cout << "Alege marginea sursă și marginea destinație (0 = sus, 1 = jos, 2 = stânga, 3 = dreapta): ";
        std::cin >> fromEdge >> toEdge;

        if (board.canMoveEdgeRow(fromEdge, toEdge, currentPlayer)) {
            board.moveEdgeRow(fromEdge, toEdge);
            std::cout << "Rândul de la marginea " << fromEdge << " a fost mutat la marginea " << toEdge << "." << std::endl;
        }
        else {
            std::cout << "Mutarea rândului nu este validă!" << std::endl;
            return false;
        }
        }
    else {
            std::cout << "Puterea " << m_power << " nu este implementată!" << std::endl;
            return false;
            }

            m_powerUsed = true;
            return true;
}
