#include "PlayingCard.h"

PlayingCard::PlayingCard(uint8_t Value, CardType Type, uint8_t x, uint8_t y) : 
	m_value(Value), m_type(Type), m_x(x), m_y(y){}

PlayingCard::PlayingCard(const PlayingCard& other)
	: m_value(other.m_value), m_type(other.m_type), m_x(other.m_x), m_y(other.m_y) {}

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
void PlayingCard::setCardPosition(uint8_t x, uint8_t y)
{
	m_x = x;
	m_y = y;
}
bool PlayingCard::canBePlacedOver(const PlayingCard& other) const
{
	return m_value > other.m_value && other.getType() != CardType::eter;
}