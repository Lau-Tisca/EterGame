#include "Card.h"

Card::Card(int value, bool isIllusion, bool isEther, const std::string& owner)
    : value(value), isIllusion(isIllusion), isEther(isEther), owner(owner) {
}

// operator <<
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << (card.isIllusion ? "I" : (card.isEther ? "E" : std::to_string(card.value)));
    return os;
}