//Player.cpp

#include "Player.h"
#include "Wizard.h"
//#include "GameBoard.h"
//#include <iostream>
//#include <stdexcept>

/*
Player::Player(const std::string& name, const Wizard& wizard)
    : name(name), wizard(wizard), hasPlacedIllusion(false), usedElementalAbility(false) {
}*/

Player::Player(const std::string& name, const Wizard& wizard)
    : name(name), wizard(wizard), hasPlacedIllusion(false), usedElementalAbility(false),
    elementalPower(MagicPower::NONE) // 🔹 Inițializare implicită
{
}

void Player::setElementalAbility(const std::string& ability) {
    elementalAbility = ability;
}

std::string Player::getElementalAbility() const {
    return elementalAbility;
}

void Player::setElementalPower(MagicPower power) {
    elementalPower = power;
}

MagicPower Player::getElementalPower() const {
    return elementalPower;
}

void Player::addToDiscardPile(const Card& card) {
    discardPile.push_back(card);
}

bool Player::hasDiscardedCards() const {
    return !discardPile.empty();
}

Card Player::getLastDiscardedCard() {
    if (discardPile.empty()) {
        throw std::runtime_error("No discarded cards available.");
    }
    Card card = discardPile.back();
    discardPile.pop_back();
    return card;
}

void Player::addCard(const Card& card) {
    hand.push_back(card);
}

void Player::removeCard(int index) {
    if (index >= 0 && index < static_cast<int>(hand.size())) {
        hand.erase(hand.begin() + index);
    }
}

void Player::resetHand() {
    hand.clear();
    std::cout << "[INFO] " << name << "'s hand has been reset.\n";
}

Card Player::getCard() {
    if (!hand.empty()) {
        return hand.back();
    }
    throw std::runtime_error("No cards available.");
}

// Metoda pentru adăugarea unei puteri elementale
void Player::addElementalPower(MagicPower power) {
    elementalPowers.push_back(power);
}

// Metoda care verifică dacă jucătorul poate folosi o putere elementala
bool Player::canUseElementalPower() const {
    return !powerUsed && !elementalPowers.empty();
}

// Metoda pentru folosirea unei puteri elementale
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

bool Player::useElementalAbility(GameBoard& board, Player& activePlayer, Player& opponent) {
    if (elementalAbility == "DESTRUCTION") {
        return board.applyDestruction(activePlayer);
    }
    else if (elementalAbility == "FLAMES") {
        return board.applyFlames(activePlayer);
    }
    else if (elementalAbility == "LAVA") {
        return board.applyLava(activePlayer);
    }
    else if (elementalAbility == "FROM_ASHES") {
        return board.applyFromAshes(activePlayer);
    }
    else if (elementalAbility == "SPARKS") {
        return board.applySparks(activePlayer);
    }
    // Adaugă și restul abilităților...

    return false;
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
