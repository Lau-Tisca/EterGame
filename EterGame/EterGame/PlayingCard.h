#pragma once
#include <cstdint>
class PlayingCard
{
public:
	enum class CardType { numbered, eter };
	PlayingCard(uint8_t Value, CardType Type); //constructor
	PlayingCard(const PlayingCard& other);     //constructor de copiere	
	uint8_t getValue();
	CardType getType();
	int getX();
	int getY();
	void setCardPosition(int x, int y);
	bool canBePlacedOver(const PlayingCard& other) const;
private:
	uint8_t m_value;
	CardType m_type;
	int m_x, m_y; //coordonatele cartii de joc in matrice
};

