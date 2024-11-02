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
};

