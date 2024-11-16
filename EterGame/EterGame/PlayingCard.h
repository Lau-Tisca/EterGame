#pragma once
#include <cstdint>
#include "Player.h"

class PlayingCard
{
public:
	enum class CardType { numbered, eter, illusion};
	PlayingCard(uint8_t Value, CardType Type, uint8_t x = -1, uint8_t y = -1, Player owner); //constructor
	PlayingCard(const PlayingCard& other);     //constructor de copiere	
	~PlayingCard(){}
	void operator=(const PlayingCard& other);
	
	bool operator==(const PlayingCard& other);

	static std::string printCardType(CardType value);
	friend std::ostream& operator<<(std::ostream& os, const PlayingCard& other);

	uint8_t getValue() const;
	CardType getType() const;
	uint8_t getX() const;
	uint8_t getY() const;
	Player getOwner() const;

	void setCardPosition(uint8_t x, uint8_t y);
	void setCardOwner(Player otherOwner);
	void setCardType(CardType type);

	bool canBePlacedOver(const PlayingCard& other) const;
	void destroyCard();
private:
	uint8_t m_value;
	CardType m_type;
	uint8_t m_x, m_y;
	Player m_owner;
	//coordonatele cartii de joc in matrice
};

