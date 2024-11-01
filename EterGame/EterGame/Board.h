#pragma once
#include <cstdint>
#include <vector>

class Board
{
private:
	//linii coloane
	uint8_t m_line, m_column;
	//matrix
	std::vector<std::vector<Card>> board;

public:
	Board(uint8_t line, uint8_t column) {
		m_line = line;
		m_column = column;
	}

	void display();

	
	

};

