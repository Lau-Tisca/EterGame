#include "Player.h"

Player::Player(std::u8string _name, std::u8string _magicPower)
{
	m_hand.clear();
	m_deck.clear();
}

Player::Player(const Player& other)
	: m_name(other.m_name)
	, m_magicPower(other.m_magicPower)
	, m_hand(other.m_hand)
	, m_deck(other.m_deck)
	, m_score(other.m_score)
	, m_roundsWon(other.m_roundsWon)
{}

void Player::playcard()
{

}

void Player::save(std::ofstream& saveFile) const {
	std::string convertedName(m_name.begin(), m_name.end());
	saveFile << convertedName << " " << m_deck.size() << " ";
	for (const auto& card : m_deck) {
		saveFile << card.getValue() << " ";
	}
	saveFile << std::endl;
	std::cout << "Starea jucătorului " << convertedName << " a fost salvată." << std::endl;
}

void Player::load(std::ifstream& loadFile) const {
	loadFile >> m_name;
	int decksize;
	loadFile >> decksize;
	m_deck.clear();
	for (int i = 0; i < decksize; i++)
	{
		int cardValue;
		loadFile >> cardValue;
		m_deck.push_back(Card(cardValue));
	}
	std::cout << "Starea jucatorului " << m_name << "a fost incarcata" << '\n';
}

bool Player::operator==(const Player& other) const
{
	if (m_name == other.m_name && m_magicPower == other.m_magicPower && m_hand == other.m_hand &&
		m_deck == other.m_deck && m_score == other.m_score && m_roundsWon == other.m_roundsWon)
		return true;
	else
		return false;
}




PlayingCard Player::removeCard(int index)
{
	PlayingCard removedCard(m_hand[index]);
	int hand_size = hand.size();
	for (int i = 0; i < hand_size; i++)
	{
		if (i == index)
		{
			for (int j = i + 1; j <= hand_size; j++)
				hand[j - 1] = hand[j];
		}
	}


	return removedCard;
}

void Player::addCard(PlayingCard card)
{
}

std::ostream& operator<<(std::ostream& os, const Player& other)
{
	os << std::string(reinterpret_cast<const char*>(other.m_name.data()), other.m_name.size()) <<
		std::string(reinterpret_cast<const char*>(other.m_magicPower.data()), other.m_magicPower.size());
	for (int i = 0; i < other.m_hand.size(); i++)
		os << other.m_hand[i];
	for (int i = 0; i < other.m_deck.size(); i++)
		os << other.m_deck[i];
	os << other.m_score << other.m_roundsWon;
	return os;
}
