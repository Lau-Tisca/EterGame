#pragma once
#include <string>

class Card {
public:
    int value;
    bool isIllusion;
    bool isEther;
    std::string owner;

    Card(int value, bool isIllusion = false, bool isEther = false, const std::string& owner = "");
};