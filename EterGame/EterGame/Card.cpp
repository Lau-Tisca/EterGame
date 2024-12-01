#include "Card.h"

Card::Card(int value, bool isIllusion, bool isEther, const std::string& owner)
    : value(value), isIllusion(isIllusion), isEther(isEther), owner(owner) {
}

int Card::getValue() const
{
    return value;
}
