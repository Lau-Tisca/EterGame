#pragma once
#include <vector>
#include <cstdint>

class Player
{
private:
    std::basic_string<char> name;
    std::string magicPower;
    std::vector<Card> hand;//(mana pe care o tine in mana);
    std::vector<Card> deck;
    int score;
    int roundsWon;

    playcard();
};

