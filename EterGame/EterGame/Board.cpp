#include "Board.h"
#include <iostream>

void Board:: display() {
	for (int i = 0; i < m_line; ++i) {
		for (int j = 0; j < m_column; ++j) {
			std::cout << board[i][j].top() << ' ';
		}
		std::cout << '\n';
	}
}

void Board::placeCard(card, line, column) {
	board[][] = card
}

uint8_t Board::setLine()
{
	return m_line;
}

uint8_t Board::getColumn()
{
	return m_column;
}
