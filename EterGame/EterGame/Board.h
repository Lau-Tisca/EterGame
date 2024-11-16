#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <stack>
#include "PlayingCard.h"

class Board
{
private:
	//lines columns
	uint8_t m_lineAndCols;
	//board
	std::vector<std::vector<std::stack<PlayingCard>>> m_board;

public:
	//constructors and destructor
	Board();
	Board(uint8_t lineAndCols);
	Board(const Board& other);
	~Board() = default;

	// operators
	Board& operator=(const Board& other);
	bool operator==(const Board& other);

	//getters
	uint8_t getLine();
	uint8_t getColumn();

	void setLineAndColumns(uint8_t line);

	bool verifyWinCondition();
	bool verifyAdjacency(uint8_t line, uint8_t column);
	void placeCard(PlayingCard card, uint8_t line, uint8_t column);
	void display();

	void reset();


};

