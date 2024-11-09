#include "Board.h"
#include <iostream>

Board::Board() {}

Board::Board(uint8_t lineAndCols)
	: m_lineAndCols(lineAndCols)
{}

Board::Board(const Board& other)
	: m_lineAndCols(other.m_lineAndCols)
	, m_board(other.m_board)
{}

Board& Board::operator=(const Board& other)
{
	m_lineAndCols = other.m_lineAndCols;
	m_board = other.m_board;
}

void Board::display() {
	for (int i = 0; i < m_lineAndCols; ++i) {
		for (int j = 0; j < m_lineAndCols; ++j) {
			std::cout << m_board[i][j].top() << ' ';
		}
		std::cout << '\n';
	}
}

void Board::reset()
{
	m_lineAndCols = 0;
	m_board.resize(m_lineAndCols);
}

void Board::placeCard(PlayingCard card, uint8_t line, uint8_t column) {
	if (m_board[line][column].empty()) {
		m_board[line][column].emplace(card);
	}
	else if (card.canBePlacedOver(m_board[line][column].top()) && card.getType() != PlayingCard::CardType::eter) {
			m_board[line][column].emplace(card);
	}
}

uint8_t Board::getLine()
{
	return m_lineAndCols;
}

uint8_t Board::getColumn()
{
	return m_lineAndCols;
}

void Board::setLineAndColumns(uint8_t lineAndCols)
{
	m_lineAndCols = lineAndCols;
	m_board.resize(lineAndCols);
}