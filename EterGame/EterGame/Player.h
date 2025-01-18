#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Card.h"
#include "Wizard.h"
#include "MagicPower.h"

class GameBoard;

class Player {

private:
    std::vector<MagicPower> elementalPowers;
    bool powerUsed = false;
public:
    std::string name;
    std::vector<Card> hand;
    Wizard wizard;
    mutable bool hasPlacedIllusion;

    Player(const std::string& name, const Wizard& wizard);

    void addCard(const Card& card);
    void removeCard(int index);

    void addElementalPower(MagicPower power);
    bool canUseElementalPower() const;
    void usePower();

    void useWizardAbility(GameBoard& board, Player& opponent, int row, int col, int destRow = -1, int destCol = -1);
    void resetWizardForGame();

    //Getter nume
    const std::string& getName() const;
    const Wizard& getWizard() const;

    // setteri
    void setWizard(const Wizard& wizard);
};