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