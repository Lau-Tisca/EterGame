#pragma once
#include <vector>
#include <cstdint>
#include <string>

class Player
{
private:
    std::u8string name;
    std::u8string magicPower;
    std::vector<Card> hand;//(mana pe care o tine in mana);
    std::vector<Card> deck;
    int score;
    int roundsWon;

public:
    Player(std::u8string _name, std::u8string _magicPower)
        :name{_name},
        magicPower{_magicPower}
    {}
    void playcard();
};

