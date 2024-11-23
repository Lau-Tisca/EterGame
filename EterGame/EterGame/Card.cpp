#include "Card.h"

Card::Card(int value, bool isIllusion = false, bool isEther = false, const std::string& owner = "")
    : value(value), isIllusion(isIllusion), isEther(isEther), owner(owner) {
}