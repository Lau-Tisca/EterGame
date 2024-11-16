#include "PlayingCard.h"

PlayingCard::PlayingCard(uint8_t Value, CardType Type, uint8_t x, uint8_t y, Player owner) : 
	m_value(Value), m_type(Type), m_x(x), m_y(y), m_owner(owner){}

PlayingCard::PlayingCard(const PlayingCard& other)
	: m_value(other.m_value), m_type(other.m_type), m_x(other.m_x), m_y(other.m_y), m_owner(other.m_owner) {}

void PlayingCard::operator=(const PlayingCard& other)
{
	m_value = other.m_value;
	m_type = other.m_type;
	m_owner = other.m_owner;
	m_x = other.m_x;
	m_y = other.m_y;
}

bool PlayingCard::operator==(const PlayingCard& other)
{
	if (m_value == other.m_value &&
		m_type == other.m_type &&
		m_owner == other.m_owner &&
		m_x == other.m_x &&
		m_y == other.m_y)
		return true;
	else
		return false;
}



std::string PlayingCard::printCardType(CardType value)
{
	switch (value){
	case CardType::numbered:
		return "numbered";
	case CardType::eter:
		return "eter";
	}
}

std::ostream& PlayingCard::operator<<(std::ostream& os)
{
	os << m_value << printCardType(m_type) << m_x << m_y << m_owner;
		return os;
}

uint8_t PlayingCard::getValue () const
{
	return m_value;
}

PlayingCard::CardType PlayingCard::getType() const
{
	return m_type;
}

uint8_t PlayingCard::getX() const
{
	return m_x;
}

uint8_t PlayingCard::getY() const
{
	return m_y;
}

Player PlayingCard::getOwner() const
{
	return m_owner;
}

void PlayingCard::setCardPosition(uint8_t x, uint8_t y)
{
	m_x = x;
	m_y = y;
}

void PlayingCard::setCardOwner(Player otherOwner)
{
	m_owner = otherOwner;
}

bool PlayingCard::canBePlacedOver(const PlayingCard& other) const
{
	return m_value > other.m_value && other.getType() != CardType::eter;
}