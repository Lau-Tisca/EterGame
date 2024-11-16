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