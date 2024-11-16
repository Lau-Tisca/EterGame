#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <stack>
#include "PlayingCard.h"
#include "Player.h"

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
	friend std::ostream& operator<<(std::ostream& os, const Board& current);
	friend std::istream& operator>>(std::istream& is);

	//getters
	
	uint8_t getLinesAndColumns();
	std::vector<std::stack<PlayingCard>> getLine(uint8_t row);

	void setLineAndColumns(uint8_t line);

	bool verifyWinCondition();
	bool verifyAdjacency(uint8_t line, uint8_t column);
	void placeCard(PlayingCard card, uint8_t line, uint8_t column);
	void placeIllusion(const PlayingCard& card, uint8_t line, uint8_t column);

	void display();
	void reset();


};

