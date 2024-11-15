#pragma once
#include <string>
#include  "Board.h"
#include "Player.h"

class Wizard
{
private:
	std::u8string m_name;
	std::u8string m_power;
	bool m_powerUsed;

public:
	// Constructor
	Wizard(const std::u8string& name, const std::u8string& power);

	//getteri
	std::u8string getName() const;
	std::u8string getPowerName() const;

	// Activeaza puterea vrajitorului
	bool usePower(Board& board, Player& currentPlayer, Player& opponent);

	// Reseteaza puterea
	void resetPower();

	void usePower(Board board) {}
};

