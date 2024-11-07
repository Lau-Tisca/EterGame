#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include "PlayingCard.h"

class Player
{
private:
    std::u8string name;
    std::u8string magicPower;
    std::vector<PlayingCard> hand;//(mana pe care o tine in mana);
    std::vector<PlayingCard> deck;
    int score;
    int roundsWon;

public:
    Player(std::u8string _name, std::u8string _magicPower) : 
        name{_name},
        magicPower{_magicPower} {

    }
    void resetDeck();
    void playcard();
    void save(std::ofstream &saveFile) const;
};

