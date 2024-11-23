#include "Player.h"
#include <iostream>
#include <stdexcept>

Player::Player(const std::string& name, const Wizard& wizard)
    : name(name), wizard(wizard) {}

void Player::addCard(const Card& card) {
    hand.push_back(card);
}

void Player::removeCard(int index) {
    if (index >= 0 && index < static_cast<int>(hand.size())) {
        hand.erase(hand.begin() + index);
    }
    else {
        throw std::out_of_range("Invalid card index!");
    }
}

void Player::useWizardAbility(GameBoard& board, int row, int col) {
    try {
        wizard.useAbility(board, row, col, *this);
    }
    catch (const std::exception& e) {
        std::cerr << "Error using wizard ability: " << e.what() << "\n";
    }
}

void Player::resetWizardForGame() {
    wizard.resetGame();
}