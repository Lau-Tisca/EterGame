#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Card.h"
#include "Wizard.h"

class Player {
public:
    std::string name;
    std::vector<Card> hand;
    Wizard wizard;
    mutable bool hasPlacedIllusion;

    Player(const std::string& name, const Wizard& wizard);

    void addCard(const Card& card);
    void removeCard(int index);

    void useWizardAbility(GameBoard& board, int row, int col);
    void resetWizardForGame();

    //Getter nume
    const std::string& getName() const;
    const Wizard& getWizard() const;

    // setteri
    void setWizard(const Wizard& wizard);
};