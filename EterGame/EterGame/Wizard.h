#pragma once

class GameBoard;
#include <string>
#include "MagicPower.h"


std::ostream& operator<<(std::ostream& os, const std::u8string& u8str);

class Wizard {
public:
    std::string name;
    MagicPower power;
    bool usedThisGame;
    bool usedThisMatch;
   

    Wizard();
    Wizard(const std::string name, MagicPower power);
    void useAbility(GameBoard& board, Player& currentPlayer, Player& opponent, int row = -1, int col = -1, int destRow = -1, int destCol = -1);
    void resetGame();
    std::string getName() const;
    MagicPower getPower() const;
    static Wizard getRandomWizard();
    static Wizard getRandomWizardDistinctFrom(const Wizard& otherWizard);
};
