//Wizard.cpp

#include "Wizard.h"
#include "GameBoard.h"
#include "Player.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

Wizard::Wizard()
    : name("Default Wizard"),
    power(MagicPower::NONE),
    usedThisGame(false),
    usedThisMatch(false) {
}

Wizard::Wizard(const std::string& name, MagicPower power)
    : name(name),
    power(power),
    usedThisGame(false),
    usedThisMatch(false) {
}

void Wizard::useAbility(GameBoard& board, Player& currentPlayer, Player& opponent, int row, int col, int destRow, int destCol) {
    if (usedThisMatch) {
        throw std::runtime_error("The magical power has already been used this match!");
    }
    /*if (usedThisGame) {
        throw std::runtime_error("The magical power has already been used this game!");
    }*/

    usedThisGame = true;
    usedThisMatch = true;

    try {
        switch (power) {
        case MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN:
            board.removeOpponentCardOverOwn(row, col, currentPlayer);
            std::cout << name << " removed an opponent's card over their own!\n";
            break;

        case MagicPower::REMOVE_ROW_WITH_OWN_CARD:
            board.removeRowWithOwnCard(row, currentPlayer);
            std::cout << name << " removed a row with their own card!\n";
            break;

        case MagicPower::COVER_OPPONENT_CARD:
            board.coverOpponentCard(row, col, currentPlayer);
            std::cout << name << " covered an opponent's card!\n";
            break;

        case MagicPower::CREATE_HOLE:
            if (!board.isSpaceEmpty(row, col)) {
                throw std::runtime_error("Cannot create a hole on a non-empty space!");
            }
            board.createHole(row, col);
            std::cout << name << " created a hole at (" << row << ", " << col << ")!\n";
            break;

        case MagicPower::MOVE_STACK_WITH_OWN_CARD:
            if (destRow == -1 || destCol == -1) {
                throw std::runtime_error("Destination row and column must be specified for this ability!");
            }
            board.moveStackWithOwnCard(row, col, destRow, destCol, currentPlayer);
            std::cout << name << " moved a stack with their own card!\n";
            break;

        case MagicPower::GAIN_EXTRA_CARD:
            board.placeEtherCard(row, col, currentPlayer);
            std::cout << name << " placed an Ether card at (" << row << ", " << col << ")!\n";
            break;

        case MagicPower::MOVE_STACK_WITH_OPPONENT_CARD:
            if (destRow == -1 || destCol == -1) {
                throw std::runtime_error("Destination row and column must be specified for this ability!");
            }
            board.moveStackWithOpponentCard(row, col, destRow, destCol, currentPlayer);
            std::cout << name << " moved a stack with an opponent's card!\n";
            break;

        case MagicPower::MOVE_ROW_TO_EDGE:
            if (destRow == -1 || destCol == -1) {
                throw std::runtime_error("Destination edge must be specified for this ability!");
            }
            board.moveRowToEdge(row, col, destRow, destCol);
            std::cout << name << " moved a row to the edge!\n";
            break;
            /*
            case MagicPower::CONTROLLED_EXPLOSION:
                board.controlledExplosion(currentPlayer);
                std::cout << name << " triggered a controlled explosion!\n";
                break;

            case MagicPower::DESTRUCTION:
                board.destruction(currentPlayer);
                std::cout << name << " caused destruction!\n";
                break;

            case MagicPower::FLAMES:
                board.flames(currentPlayer, opponent);
                std::cout << name << " unleashed flames!\n";
                break;*/

        default:
            throw std::runtime_error("Invalid magical power!");
        }
    }
    catch (const std::exception& e) {
        // Revocă marcajele `usedThisMatch` și `usedThisGame` dacă execuția a eșuat
        usedThisGame = false;
        usedThisMatch = false;
        throw; // Retrimite excepția către apelant
    }

    std::cout << name << " used their magical power!\n";
}

void Wizard::resetGame() {
    usedThisGame = false;
}

std::string Wizard::getName() const
{
    return name;
}

MagicPower Wizard::getPower() const {
    return power; // Asumăm că `power` este un membru al clasei `Wizard`.
}

Wizard Wizard::getRandomWizard()
{
    static const std::vector<Wizard> availableWizards = {
        Wizard("Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD),
        Wizard("Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN),
        Wizard("Earth Mage", MagicPower::CREATE_HOLE),
        Wizard("Air Mage", MagicPower::MOVE_STACK_WITH_OWN_CARD),
        Wizard("Light Mage", MagicPower::GAIN_EXTRA_CARD),
        Wizard("Dark Mage", MagicPower::COVER_OPPONENT_CARD),
        Wizard("Water Mage", MagicPower::MOVE_STACK_WITH_OPPONENT_CARD),
        Wizard("Storm Mage", MagicPower::MOVE_ROW_TO_EDGE)
    };

    srand(static_cast<unsigned>(time(0))); // Inițializează generatorul de numere aleatoare
    int randomIndex = rand() % availableWizards.size();
    return availableWizards[randomIndex];
}

Wizard Wizard::getRandomWizardDistinctFrom(const Wizard& otherWizard) {
    static const std::vector<Wizard> availableWizards = {
        Wizard("Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD),
        Wizard("Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN),
        Wizard("Earth Mage", MagicPower::CREATE_HOLE),
        Wizard("Air Mage", MagicPower::MOVE_STACK_WITH_OWN_CARD),
        Wizard("Light Mage", MagicPower::GAIN_EXTRA_CARD),
        Wizard("Dark Mage", MagicPower::COVER_OPPONENT_CARD),
        Wizard("Water Mage", MagicPower::MOVE_STACK_WITH_OPPONENT_CARD),
        Wizard("Storm Mage", MagicPower::MOVE_ROW_TO_EDGE)
    };

    srand(static_cast<unsigned>(time(0))); // Inițializează generatorul de numere aleatoare

    Wizard randomWizard;
    do {
        int randomIndex = rand() % availableWizards.size();
        randomWizard = availableWizards[randomIndex];
    } while (randomWizard.getName() == otherWizard.getName());

    return randomWizard;
}
