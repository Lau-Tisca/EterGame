#include "Player.h"

Player::Player(std::u8string _name, std::u8string _magicPower)
{
	hand.clear();
	deck.clear();
}

void Player::playcard()
{

}

void Player::save(std::ofstream& saveFile) const {
    std::string convertedName(name.begin(), name.end());
    saveFile << convertedName << " " << deck.size() << " ";
    for (const auto& card : deck) {
        saveFile << card.getValue() << " ";
    }
    saveFile << std::endl;
    std::cout << "Starea jucătorului " << convertedName << " a fost salvată." << std::endl;
}

void Player::load(std::ifstream& loadFile) const {
    loadFile >> name;
    int decksize;
    loadFile >> decksize;
    deck.clear();
    for (int i = 0; i < decksize; i++)
    {
        int cardValue;
        loadFile >> cardValue;
        deck.push_back(Card(cardValue));
    }
    std::cout << "Starea jucatorului " << name << "a fost incarcata" <<'\n';
}