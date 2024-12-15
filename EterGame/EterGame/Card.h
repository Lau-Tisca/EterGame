#pragma once
#include <string>

class Card {
public:
    int value;
    bool isIllusion;
    bool isEther;
    std::string owner;

    //Constructor
    Card(int value, bool isIllusion = false, bool isEther = false, const std::string& owner = "");

    // Supraincarcare <<
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend bool operator==(Card a, Card b);
};