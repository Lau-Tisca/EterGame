#pragma once
#include <cstdint>
class PlayingCard
{
public:
	enum class CardType { numbered, eter };
	PlayingCard(uint8_t Value, CardType Type, uint8_t x=-1, uint8_t y=-1); //constructor
	PlayingCard(const PlayingCard& other);     //constructor de copiere	
	uint8_t getValue() const;
	CardType getType() const;
	uint8_t getX() const;
	uint8_t getY() const;
	void setCardPosition(uint8_t x, uint8_t y);
	bool canBePlacedOver(const PlayingCard& other) const;
private:
	uint8_t m_value;
	CardType m_type;
	uint8_t m_x, m_y;
	//coordonatele cartii de joc in matrice
};

