#include "Player.h"
#include "Wizard.h"

Player::Player(const std::string& name, const Wizard& wizard)
    : name(name), wizard(wizard), hasPlacedIllusion(false) {
}

void Player::addCard(const Card& card) {
    hand.push_back(card);
}

void Player::removeCard(int index) {
    if (index >= 0 && index < static_cast<int>(hand.size())) {
        hand.erase(hand.begin() + index);
    }
}

void Player::addElementalPower(MagicPower power) {
    elementalPowers.push_back(power);
}

bool Player::canUseElementalPower() const {
    return !powerUsed && !elementalPowers.empty();
}

void Player::usePower() {
    if (canUseElementalPower()) {
        // Exemplu: marchez că puterea a fost utilizată
        powerUsed = true;
        std::cout << name << " used an elemental power.\n";
    }
    else {
        std::cout << name << " cannot use an elemental power right now.\n";
    }
}


// Abilitatea vrajitorului
void Player::useWizardAbility(GameBoard& board, Player& opponent, int row, int col, int destRow, int destCol) {
    wizard.useAbility(board, *this, opponent, row, col, destRow, destCol);
}

void Player::resetWizardForGame() {
    wizard.resetGame();
}

const std::string& Player::getName() const {
    return name;
}

const Wizard& Player::getWizard() const
{
    // TODO: insert return statement here
    return wizard;
}

void Player::setWizard(const Wizard& wizard) {
    this->wizard = wizard;
    std::cout << name << " has been assigned the wizard: " << wizard.getName() << " with power "
        << static_cast<int>(wizard.getPower()) << ".\n";
}