#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include "GameBoard.h"

#include "Wizard.h"
class Player {
public:
    std::string name;
    std::vector<Card> hand;
    Wizard wizard;

    Player(const std::string& name, const Wizard& wizard);

    void addCard(const Card& card);
    void removeCard(int index);

    void useWizardAbility(GameBoard& board, int row, int col);
    void resetWizardForGame();
};