#pragma once
#include <string>

class Card {
private:
    int value;

public:
    bool isIllusion;
    bool isEther;
    std::string owner;

    Card(int value, bool isIllusion = false, bool isEther = false, const std::string& owner = "");

    int getValue() const;
};