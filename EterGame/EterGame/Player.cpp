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
