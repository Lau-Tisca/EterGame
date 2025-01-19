//Wizard.h

#pragma once

class GameBoard;

#include <string>
#include "MagicPower.h"

class Player;
class GameBoard;

class Wizard {
public:
    std::string name;
    MagicPower power;
    bool usedThisGame;
    bool usedThisMatch;

    //Constructor
    Wizard(); //Constructor implicit
    Wizard(const std::string& name, MagicPower power);

    //Metode
    // vechi - void useAbility(GameBoard& board, int row, int col, Player& currentPlayer, int destRow = -1, int destCol = -1);
    void useAbility(GameBoard& board, Player& currentPlayer, Player& opponent, int row = -1, int col = -1, int destRow = -1, int destCol = -1);

    void resetGame();

    //Getteri
    std::string getName() const;
    MagicPower getPower() const;
    static Wizard getRandomWizard();
    static Wizard getRandomWizardDistinctFrom(const Wizard& otherWizard);
};