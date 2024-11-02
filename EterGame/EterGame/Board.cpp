#include "Board.h"
#include <iostream>

Board::Board(){}

Board::Board(uint8_t line, uint8_t column)
	: m_line(line)
	, m_column(column)
{}

Board::Board(const Board& other)
	: m_line(other.m_line)
	, m_column(other.m_column)
	, m_board(other.m_board)
{}

Board& Board::operator=(const Board & other)
{
	m_line = other.m_line;
	m_column = other.m_column;
	m_board = other.m_board;
}

void Board:: display() {
	for (int i = 0; i < m_line; ++i) {
		for (int j = 0; j < m_column; ++j) {
			std::cout << m_board[i][j].top() << ' ';
		}
		std::cout << '\n';
	}
}

void Board::placeCard(PlayingCard card, uint8_t line, uint8_t column) {
	m_board[line][column].top() = card;
}

uint8_t Board::getLine()
{
	return m_line;
}

uint8_t Board::getColumn()
{
	return m_column;
}
