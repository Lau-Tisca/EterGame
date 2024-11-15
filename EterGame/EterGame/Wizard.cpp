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
bool Wizard::usePower(Board& board) {
    if (m_powerUsed) {
        std::cout << "Puterea vrăjitorului " << std::string(m_name.begin(), m_name.end()) << " a fost deja utilizată!" << std::endl;
        return false;
    }

    if (m_power == "Explosion") {
        // Exemplu: Șterge toate cărțile dintr-un rând
        int row = 0;  // Aici poți primi input pentru a alege rândul
        for (auto& cell : board.getLine()) {
            cell = nullptr;
        }
        std::cout << "Explozie activată de " << std::string(m_name.begin(), m_name.end()) << "!" << std::endl;
    }
    else if (m_power == "Illusion") {
        // Exemplu: Plasează o carte falsă
        std::cout << std::string(m_name.begin(), m_name.end()) << " a plasat o carte iluzie!" << std::endl;
    }

    m_powerUsed = true;  // Marchez că puterea a fost utilizată
    return true;
}