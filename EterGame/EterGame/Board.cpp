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

bool Board::operator==(const Board& other)
{
	if (m_lineAndCols == other.m_lineAndCols;
		m_board == other.m_board)
		return true;
	else return false;
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
		if (std::find(m_board[i].begin(), m_board[i].end(), nullptr) != m_board[i].end()) {
			std::cout << "The board is full\n";
			return true;
		}
	}

	for (const auto& row : m_board) {
		if (std::all_of(row.begin(), row.end(), [&](const PlayingCard* card) { return card != nullptr && card->getOwner() == row[0].top().getOwner(); })) {
			return true;
		}
	}

	for (size_t col = 0; col < m_board[0].size(); ++col) {
		if (std::all_of(m_board.begin(), m_board.end(), [&](const std::vector<PlayingCard*>& row) { return row[col] != nullptr && row[col]->getOwner() == m_board[0][col].top().getOwner(); })) {
			return true;
		}
	}


	bool diag1 = true, diag2 = true;
	for (int i = 0; i < m_board[0].size() - 1; i++) {
		if (m_board[i][i].top().getOwner() != m_board[i + 1][i + 1].top().getOwner())
			diag1 = false;
	}
	for (int i = m_board[0].size(); i > 0; i--) {
		if (m_board[i][getLinesAndColumns() - 1 - i].top().getOwner() != m_board[i][getLinesAndColumns() - 1 - i].top().getOwner())
			diag2 = false;
	}

	return diag1 || diag2;

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
			if (!m_board[nLine][nColumn].empty()) {
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
			if (card.getType() == PlayingCard::CardType::illusion) {
				if (card.canBePlacedOver(m_board[line][column].top()))
					m_board[line][column].emplace(card);
				else
					card.destroyCard();
			}
			else {
				m_board[line][column].emplace(card);
			}
		}
	}
	else {
		std::cout << "You chose an invalid position!\n";
	}
}

void Board::placeIllusion(const PlayingCard& card, uint8_t line, uint8_t column)
{
	if (verifyAdjacency(line, column)) {
		if (m_board[line][column].empty()) {
			m_board[line][column].emplace(card);
			m_board[line][column].top().setCardType(PlayingCard::CardType::illusion);
		}
	}
}

uint8_t Board::getLinesAndColumns()
{
	return m_lineAndCols;
}

std::vector<std::stack<PlayingCard>> Board::getLine(uint8_t row)
{
	std::vector<std::stack<PlayingCard>> rowToReturn;
	rowToReturn = m_board[row];

	return rowToReturn;
}


void Board::setLineAndColumns(uint8_t lineAndCols)
{
	m_lineAndCols = lineAndCols;
	m_board.resize(lineAndCols);
}

std::ostream& operator<<(std::ostream& os, const Board& current)
{
	for (int i = 0; i < current.m_lineAndCols; ++i) {
		for (int j = 0; j < current.m_lineAndCols; ++j) {
			os << current.m_board[i][j].top() << ' ';
		}
		os << '\n';
	}
}

