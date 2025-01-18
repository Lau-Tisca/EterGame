#pragma once
#include <string>
#include <iostream>

class Card {
public:
    int value;
    int originalValue;
    bool isIllusion;
    bool isEther;
    std::string owner;

    //Constructor
    Card(int value, bool isIllusion = false, bool isEther = false, const std::string& owner = "");

    // Supraincarcare <<
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend bool operator==(Card a, Card b);
};