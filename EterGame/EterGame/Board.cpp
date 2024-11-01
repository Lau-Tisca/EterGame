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