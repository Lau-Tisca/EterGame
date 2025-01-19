//Player.h

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Card.h"
#include "Wizard.h"
#include "MagicPower.h"
#include "GameBoard.h"

class GameBoard;

class Player {
private:
    std::vector<MagicPower> elementalPowers;
    bool powerUsed = false;
    std::string elementalAbility;
    std::vector<Card> discardPile;
    MagicPower elementalPower;
public:
    std::string name;
    std::vector<Card> hand;
    Wizard wizard;
    mutable bool hasPlacedIllusion;
    bool usedElementalAbility;
    Player(const std::string& name, const Wizard& wizard);
    Player(const std::string& name) : name(name) {}
    void setElementalAbility(const std::string& ability);
    std::string getElementalAbility() const;

    void setElementalPower(MagicPower power);
    MagicPower getElementalPower() const;
    const std::vector<Card>& getHand() const { return hand; }
    void addToDiscardPile(const Card& card);
    bool hasDiscardedCards() const;
    Card getLastDiscardedCard();

    void addCard(const Card& card);
    void removeCard(int index);

    void resetHand();
    Card getCard();

    // Noi metode pentru puteri elementale
    void addElementalPower(MagicPower power);
    bool canUseElementalPower() const;
    void usePower();

    // Abilitatea vrajitorului
    void useWizardAbility(GameBoard& board, Player& opponent, int row, int col, int destRow = -1, int destCol = -1);
    void resetWizardForGame();

    bool useElementalAbility(GameBoard& board, Player& activePlayer, Player& opponent);

    //Getter nume
    const std::string& getName() const;
    const Wizard& getWizard() const;

    // setteri
    void setWizard(const Wizard& wizard);
};
