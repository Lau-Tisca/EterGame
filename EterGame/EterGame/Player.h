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
    std::u8string m_name;
    std::u8string m_magicPower;
    std::vector<PlayingCard> m_hand;//(mana pe care o tine in mana);
    std::vector<PlayingCard> m_deck;
    int m_score;
    int m_roundsWon;

public:
    Player(std::u8string _name, std::u8string _magicPower) : 
        m_name{_name},
        m_magicPower{_magicPower}{
    }
    Player(const Player& other);
    std::uint16_t getDeckSize();
    void resetDeck();
    
    void playcard();
    void save(std::ofstream &saveFile) const;
    void load(std::ifstream& loadFile) const;

    bool operator == (const Player & other) const;
    friend std::ostream& operator<<(std::ostream& os, const Player& other);
};

