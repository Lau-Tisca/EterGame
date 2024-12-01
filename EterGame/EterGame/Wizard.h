#pragma once
#include <string>
#include "MagicPower.h"
#include "GameBoard.h"

std::ostream& operator<<(std::ostream& os, const std::u8string& u8str);

class Wizard {
public:
    const std::u8string name;
    MagicPower power;
    bool usedThisGame;
    bool usedThisMatch;
    static std::string abilityDescription;

    Wizard(const std::u8string& name, MagicPower power);
    void useAbility(GameBoard& board, int row, int col, Player& currentPlayer, int destRow = -1, int destCol = -1);
    void resetGame();
    std::u8string getName() const {}
};
