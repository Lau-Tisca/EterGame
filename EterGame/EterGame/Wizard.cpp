#include "MagicPower.h"
#include "Wizard.h"
#include "GameBoard.h"
#include "Player.h"

#include <stdexcept>
#include <iostream>
#include <string>

/*
Wizard::Wizard(const std::string& name, MagicPower power)
    : name(name), power(power), usedThisGame(false), usedThisMatch(false) {
}*/

Wizard::Wizard()
    : name("Default Wizard"),
    power(MagicPower::NONE),
    usedThisGame(false),
    usedThisMatch(false) {
}

Wizard::Wizard(const std::u8string& name, MagicPower power)
    : name(name), power(power) {
}

std::ostream& operator<<(std::ostream& os, const std::u8string& u8str)
{
    return os << std::string(u8str.begin(), u8str.end());
}

// Getteri
std::u8string Wizard::getName() const {
    return name;
}

// puterile
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
            break;

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
    usedThisGame = false; // Resetăm utilizarea doar pentru jocul curent
}