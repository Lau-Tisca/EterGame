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



bool Board::verifyWinCondition()
{
	for (int i = 0; i < m_lineAndCols; i++) {
		if (std::find(m_board[i].begin(), m_board[i].end(), NULL) != m_board.end()) {
			std::cout << "The board is full\n";
			return true;
		}
	}

}

bool Board::verifyAdjacency(uint8_t line, uint8_t column)
{
	int rows = m_board.size();
	int cols = m_board[0].size();

	int directions[8][2] = {
		{-1, 0},  // up
		{1, 0},   // down
		{0, -1},  // left
		{0, 1},   // right
		{-1, -1}, // up-left
		{-1, 1},  // up_right
		{1, -1},  // down-left
		{1, 1}    // down-right
	};

	for (int d = 0; d < 8; ++d) {
		int nLine = line + directions[d][0];
		int nColumn = column + directions[d][1];

		if (nLine >= 0 && nLine < rows && nColumn >= 0 && nColumn < cols) {
			if (m_board[nLine][nColumn].top() != NULL) {
				return true;
			}
		}
	}
}

void Board::placeCard(PlayingCard card, uint8_t line, uint8_t column) {
	if (verifyAdjacency(line, column)) {
		if (m_board[line][column].empty()) {
			m_board[line][column].emplace(card);
		}
		else if (card.canBePlacedOver(m_board[line][column].top()) && card.getType() != PlayingCard::CardType::eter) {
			m_board[line][column].emplace(card);
		}
	}
	else {
		std::cout << "You chose an invalid position!\n";
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