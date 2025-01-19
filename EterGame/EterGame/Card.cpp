#include "Card.h"

Card::Card()
    : value(0),
    isIllusion(false),
    isEther(false),
    owner(""),
    originalValue(0) {
}

Card::Card(int value, bool isIllusion, bool isEther, const std::string& owner)
    : value(value),
    isIllusion(isIllusion),
    isEther(isEther),
    owner(owner),
    originalValue(value) {
}

void Card::setOwner(const std::string& player)
{
    owner = player;
}

std::string Card::getOwner() const {
    return owner;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << (card.isIllusion ? "I" : (card.isEther ? "E" : std::to_string(card.value)));
    return os;
}

bool operator==(Card a, Card b)
{
    if (a.value == b.value)
        return true;
    return false;
}