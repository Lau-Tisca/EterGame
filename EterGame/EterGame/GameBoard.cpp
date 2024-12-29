#include "GameBoard.h"

// Constructor principal
GameBoard::GameBoard(int size, Player& p1, Player& p2)
	: size(size),
	explosionOccurred(false),
	isFirstMove(true),
	board(size, std::vector<std::vector<std::optional<Card>>>(size, std::vector<std::optional<Card>>())),
	player1(&p1),
	player2(&p2) {
	std::cout << "Initialized board with size: " << size << "x" << size << "\n";
}

// Constructor secundar
GameBoard::GameBoard(int size)
	: size(size),
	explosionOccurred(false),
	isFirstMove(true),
	board(size, std::vector<std::vector<std::optional<Card>>>(size, std::vector<std::optional<Card>>())),
	player1(nullptr),
	player2(nullptr) {
	std::cout << "Initialized board with size: " << size << "x" << size << "\n";
}

// Getteri
int GameBoard::getSize() const {
	return size;
}

// Setteri
void GameBoard::setFirstMove(bool value)
{
	isFirstMove = value;
	std::cout << "First move reset to: " << (isFirstMove ? "true" : "false") << "\n";
}

// pentru explozie
void GameBoard::addHole(int row, int col) {
	holes.emplace_back(row, col);
}

//pentru abilitatea de trasformare a unui spatiu gol intr-o groapa
void GameBoard::createHole(int row, int col) {
	if (!isValidPosition(row, col)) {
		throw std::runtime_error("Invalid position on the board!");
	}

	if (board[row][col].has_value()) {
		throw std::runtime_error("Cannot create a hole on a non-empty space!");
	}

	if (isHole(row, col)) {
		throw std::runtime_error("There is already a hole at this position!");
	}

	// Transformă spațiul gol într-o groapă
	addHole(row, col);
	std::cout << "Created a hole at (" << row << ", " << col << ").\n";
}

bool GameBoard::isHole(int row, int col) const {
	return std::find(holes.begin(), holes.end(), std::make_pair(row, col)) != holes.end();
}

bool GameBoard::placeCard(int row, int col, const Card card, const Player& currentPlayer) {
	if (!isValidPosition(row, col) || isHole(row, col)) {
		return false; // Nu permite plasarea pe o groapă sau pe o pozitie invalida
	}
	/* Nu mai e buna (eroare la '='
	if (!board[row][col].has_value() || board[row][col]->value < card.value) {
		card.owner = currentPlayer.name; // Asociaza cartea cu jucatorul curent
		board[row][col] = card;
		return true;
	}*/

	if (!board[row][col].has_value() || board[row][col]->value < card.getValue()) {
		board[row][col] = Card(card.getValue(), card.isIllusion, card.isEther, currentPlayer.name); // Creează o copie cu proprietar setat
		return true;
	}
	return false;
}

std::string GameBoard::checkWinCondition(const Player& player) const {
	// Verificare linii orizontale
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			bool horizontalWin = true;
			for (int d = 0; d < size; ++d) {
				if (board[row][d].empty() || !board[row][d][0].has_value() || board[row][d][0]->owner != player.name) {
					horizontalWin = false;
					break;
				}
			}
			if (horizontalWin) {
				return "Horizontal line at row " + std::to_string(row);
			}
		}
	}

	// Verificare coloane verticale
	for (int col = 0; col < size; ++col) {
		for (int row = 0; row < size; ++row) {
			bool verticalWin = true;
			for (int d = 0; d < size; ++d) {
				if (board[d][col].empty() || !board[d][col][0].has_value() || board[d][col][0]->owner != player.name) {
					verticalWin = false;
					break;
				}
			}
			if (verticalWin) {
				return "Vertical line at column " + std::to_string(col);
			}
		}
	}

	// Verificare diagonală principală (\)
	bool diagonalWin1 = true;
	for (int d = 0; d < size; ++d) {
		if (board[d][d].empty() || !board[d][d][0].has_value() || board[d][d][0]->owner != player.name) {
			diagonalWin1 = false;
			break;
		}
	}
	if (diagonalWin1) {
		return "Main diagonal (\\)";
	}

	// Verificare diagonală secundară (/)
	bool diagonalWin2 = true;
	for (int d = 0; d < size; ++d) {
		if (board[d][size - 1 - d].empty() || !board[d][size - 1 - d][0].has_value() || board[d][size - 1 - d][0]->owner != player.name) {
			diagonalWin2 = false;
			break;
		}
	}
	if (diagonalWin2) {
		return "Secondary diagonal (/)";
	}

	// Dacă nu există o condiție de câștig
	return "";
}

void GameBoard::applyExplosion(const std::vector<std::pair<int, int>>& positions, int holeCount)
{
	std::cout << "Explosion triggered!\n";
	for (const auto& pos : positions) {
		int row = pos.first, col = pos.second;
		if (board[row][col].has_value()) {
			std::cout << "Card at (" << row << ", " << col << ") removed.\n";
			board[row][col].reset();
		}
		// Transformăm unele poziții în gropi
		if (holeCount > 0) {
			addHole(row, col);
			std::cout << "Hole created at (" << row << ", " << col << ").\n";
			--holeCount;
		}
	}
}

void GameBoard::printBoard() const {
	std::cout << "\nCurrent Board State:\n";

	// Afișează etichetele coloanelor
	std::cout << "   ";
	for (int col = 0; col < size; ++col) {
		std::cout << col << "  ";
	}
	std::cout << "\n";

	// Iterează prin fiecare rând
	for (int row = 0; row < size; ++row) {
		std::cout << row << " |"; // Eticheta rândului

		for (int col = 0; col < size; ++col) {
			if (isHole(row, col)) {
				std::cout << " H ";
			}
			else if (!board[row][col].empty()) {
				const auto& topCard = board[row][col].back();
				if (topCard.has_value()) {
					std::cout << " {" << topCard->value << "} ";
				}
				else {
					std::cout << " . ";
				}
			}
			else {
				std::cout << " . ";
			}
		}
		std::cout << "\n";
	}
}



bool GameBoard::triggerExplosion(Player& currentPlayer) {
	if (explosionOccurred) {
		std::cout << "Explosion has already occured. No other can happen.\n";
		return false;
	}

	// Verifică dacă există două rânduri complet ocupate
	int fullLines = 0;
	for (int i = 0; i < size; ++i) {
		if (isLineFull(i, 0, 0, 1) || isLineFull(0, i, 1, 0)) {
			++fullLines;
		}
	}
	if (fullLines < 2) return false;

	// Actualizează starea pentru a preveni alte explozii
	if (fullLines >= 2) {
		explosionOccurred = true;
	}

	// Alege o carte de explozie aleatorie (3x3 sau 4x4 în funcție de dimensiunea tablei)
	srand(static_cast<unsigned>(time(0)));
	std::vector<std::pair<int, int>> affectedPositions = generateExplosionPattern();

	// Aplică efectele exploziei
	std::cout << "\nExplosion triggered! Affected positions and actions:\n";
	for (const auto& [row, col] : affectedPositions) {
		if (isValidPosition(row, col) && board[row][col].has_value()) {
			if (rand() % 2 == 0) {
				// Elimină cartea din joc
				std::cout << " - (" << row << ", " << col << "): Card with value "
					<< board[row][col]->value << " removed from play.\n";
				board[row][col].reset();
			}
			else {
				if (currentPlayer.hand.size() < 10) {
					std::cout << " - (" << row << ", " << col << "): Card with value "
						<< board[row][col]->value << " returned to "
						<< currentPlayer.name << "'s hand.\n";
					currentPlayer.addCard(board[row][col]->value);
				}
				else {
					std::cout << " - (" << row << ", " << col << "): Card with value "
						<< board[row][col]->value << " cannot be returned; hand is full.\n";
				}
				board[row][col].reset();
			}
		}
	}

	// Afișează tabla actualizată
	std::cout << "\nUpdated board after explosion:\n";
	printBoard();

	return true;
}

/*
 * Elimină o carte a adversarului de pe tablă care acoperă o carte proprie
 */

void GameBoard::coverOpponentCard(int row, int col, Player& currentPlayer) {
	/*if (!isValidPosition(row, col)) {
		throw std::runtime_error("Invalid position on the board!");
	}*/
	// Verifică dacă coordonatele sunt valide
	if (row < 0 || row >= board.size() || col < 0 || col >= board[row].size()) {
		throw std::out_of_range("Invalid coordinates: row or column out of bounds.");
	}

	// Verifică dacă există o carte la coordonate
	if (!board[row][col].has_value()) {
		throw std::runtime_error("No card at the given position to cover!");
	}

	const Card& topCard = *board[row][col];

	// Verificare: nu poți acoperi propria iluzie
	if (topCard.owner == currentPlayer.name && topCard.isIllusion) {
		throw std::runtime_error("You cannot cover your own Illusion!");
	}

	if (topCard.isIllusion) {
		// Iluzia este întoarsă cu fața în sus
		std::cout << "The Illusion at (" << row << ", " << col << ") is revealed!\n";

		// Dacă valoarea cărții oponentului este <= 1, elimină cartea oponentului
		auto it = std::find_if(currentPlayer.hand.begin(), currentPlayer.hand.end(),
			[&](const Card& card) { return card.value <= 1; });

		if (it != currentPlayer.hand.end()) {
			std::cout << "Your card is eliminated because its value is <= 1!\n";
			//currentPlayer.removeCard(std::distance(currentPlayer.hand.begin(), it));


			currentPlayer.removeCard(static_cast<int>(std::distance(currentPlayer.hand.begin(), it)));

			return; // Tura se încheie
		}
	}

	// Restul regulilor pentru acoperirea unei cărți normale
	// Găsește o carte proprie de valoare strict mai mică
	auto it = std::find_if(currentPlayer.hand.begin(), currentPlayer.hand.end(),
		[&](const Card& card) {
			return card.value < topCard.value && !card.isIllusion;
		});

	if (it == currentPlayer.hand.end()) {
		throw std::runtime_error("No valid card in hand to cover the opponent's card!");
	}

	// Plasează cartea proprie peste cea a oponentului
	board[row][col] = Card(it->value, it->isIllusion, it->isEther, currentPlayer.name);

	// Elimină cartea din mână
	//currentPlayer.removeCard(std::distance(currentPlayer.hand.begin(), it));
	currentPlayer.removeCard(static_cast<int>(std::distance(currentPlayer.hand.begin(), it)));

	std::cout << "Covered opponent's card at (" << row << ", " << col
		<< ") with your card of value " << board[row][col]->value << ".\n";
}

/*
 * Mută un teanc de cărți cu propria carte deasupra pe o altă poziție goală pe tablă.
*/
void GameBoard::moveStackWithOwnCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer) {
	if (!isValidPosition(srcRow, srcCol) || !isValidPosition(destRow, destCol)) {
		throw std::runtime_error("Invalid position on the board!");
	}

	if (!board[srcRow][srcCol].has_value()) {
		throw std::runtime_error("No stack exists at the source position!");
	}

	if (board[destRow][destCol].has_value()) {
		throw std::runtime_error("The destination position is not empty!");
	}

	const Card& topCard = *board[srcRow][srcCol];
	if (topCard.owner != currentPlayer.name) {
		throw std::runtime_error("You can only move stacks where your card is on top!");
	}

	// Muta teancul
	board[destRow][destCol] = board[srcRow][srcCol];
	board[srcRow][srcCol].reset();

	std::cout << "Moved stack from (" << srcRow << ", " << srcCol << ") to (" << destRow << ", " << destCol << ").\n";
}

/*
 * Capata o extra carte Eter care se plasează imediat pe tabla.
 */
void GameBoard::placeEtherCard(int row, int col, const Player& currentPlayer) {
	if (!isValidPosition(row, col) || isHole(row, col)) {
		throw std::runtime_error("Cannot place Ether card on this position!");
	}
	if (board[row][col].has_value()) {
		throw std::runtime_error("Position already occupied!");
	}

	// Plasează cartea Eter pe tablă
	board[row][col] = Card(0, false, true, currentPlayer.name);
	std::cout << "Placed Ether card at (" << row << ", " << col << ") for " << currentPlayer.name << ".\n";
}

/*
 * Muta un teanc de cărți cu cartea adversarului deasupra pe o alta poziție goală pe tabla.
 */
void GameBoard::moveStackWithOpponentCard(int srcRow, int srcCol, int destRow, int destCol, const Player& currentPlayer) {
	if (!isValidPosition(srcRow, srcCol) || !isValidPosition(destRow, destCol)) {
		throw std::runtime_error("Invalid position on the board!");
	}

	if (!board[srcRow][srcCol].has_value()) {
		throw std::runtime_error("No stack exists at the source position!");
	}

	if (board[destRow][destCol].has_value() || isHole(destRow, destCol)) {
		throw std::runtime_error("The destination position is not empty or is a hole!");
	}

	const Card& topCard = *board[srcRow][srcCol];
	if (topCard.owner == currentPlayer.name) {
		throw std::runtime_error("You can only move stacks where the opponent's card is on top!");
	}

	// Muta teancul
	board[destRow][destCol] = board[srcRow][srcCol];
	board[srcRow][srcCol].reset();

	std::cout << "Moved stack with opponent's card from (" << srcRow << ", " << srcCol
		<< ") to (" << destRow << ", " << destCol << ").\n";
}

/*
	 *Mută oricare rând aflat la “marginea” tablei pe o altă “margine”. Rândul mutat trebuie să ocupe cel puțin 3 poziții.
	*/
void GameBoard::moveRowToEdge(int srcRow, int srcCol, int destRow, int destCol) {
	// Verifică dacă sursa și destinația sunt la marginea tablei
	if (!((srcRow == 0 || srcRow == size - 1 || srcCol == 0 || srcCol == size - 1) &&
		(destRow == 0 || destRow == size - 1 || destCol == 0 || destCol == size - 1))) {
		throw std::runtime_error("Source and destination must be on the edges of the board!");
	}

	// Verifică dacă rândul/coloana sursă este validă
	int occupiedPositions = 0;
	if (srcRow == 0 || srcRow == size - 1) { // Mutare pe orizontală
		for (int col = 0; col < size; ++col) {
			if (board[srcRow][col].has_value()) {
				++occupiedPositions;
			}
		}
	}
	else if (srcCol == 0 || srcCol == size - 1) { // Mutare pe verticală
		for (int row = 0; row < size; ++row) {
			if (board[row][srcCol].has_value()) {
				++occupiedPositions;
			}
		}
	}
	else {
		throw std::runtime_error("Invalid source row/column!");
	}

	if (occupiedPositions < 3) {
		throw std::runtime_error("The row/column must occupy at least 3 positions!");
	}

	// Verifică dacă destinația este goală
	if (destRow == 0 || destRow == size - 1) { // Mutare pe orizontală
		for (int col = 0; col < size; ++col) {
			if (board[destRow][col].has_value()) {
				throw std::runtime_error("Destination row is not empty!");
			}
		}
	}
	else if (destCol == 0 || destCol == size - 1) { // Mutare pe verticală
		for (int row = 0; row < size; ++row) {
			if (board[row][destCol].has_value()) {
				throw std::runtime_error("Destination column is not empty!");
			}
		}
	}
	else {
		throw std::runtime_error("Invalid destination row/column!");
	}

	// Mută rândul/coloana
	if (srcRow == 0 || srcRow == size - 1) { // Mutare pe orizontală
		for (int col = 0; col < size; ++col) {
			board[destRow][col] = board[srcRow][col];
			board[srcRow][col].reset();
		}
	}
	else if (srcCol == 0 || srcCol == size - 1) { // Mutare pe verticală
		for (int row = 0; row < size; ++row) {
			board[row][destCol] = board[row][srcCol];
			board[row][srcCol].reset();
		}
	}

	std::cout << "Moved row/column from edge (" << srcRow << ", " << srcCol
		<< ") to edge (" << destRow << ", " << destCol << ").\n";
}

void GameBoard::controlledExplosion(Player& currentPlayer)
{
	int holeCount = 0;
	auto pattern = ExplosionPattern::generateExplosionPattern(size, holeCount);
	applyExplosion(pattern, holeCount);
	std::cout << "Controlled explosion activated!\n";
}

bool GameBoard::isValidPosition(int row, int col) const {
	return row >= 0 && row < size && col >= 0 && col < size;
}

bool GameBoard::checkLine(const Player& player, int startRow, int startCol, int dRow, int dCol) const {
	//int count = 0;
	for (int i = 0; i < size; ++i) {
		int row = startRow + i * dRow;
		int col = startCol + i * dCol;

		if (!isValidPosition(row, col))
			return false;
		/*
		if (board[row][col].has_value() && board[row][col]->value > 0) {
			count++;
		}
		else {
			count = 0;
		}

		if (count == size) return true;
		*/

		if (!board[row][col].has_value() || board[row][col]->owner != player.name) {
			return false;
		}
	}
	return false; // Linia aparține complet jucătorului curent
}

bool GameBoard::isLineFull(int startRow, int startCol, int dRow, int dCol) const {
	for (int i = 0; i < size; ++i) {
		int row = startRow + i * dRow;
		int col = startCol + i * dCol;

		if (!isValidPosition(row, col) || !board[row][col].has_value()) {
			return false;
		}
	}
	return true;
}

std::vector<std::pair<int, int>> GameBoard::generateExplosionPattern() {
	std::vector<std::pair<int, int>> positions;
	int effects = (size == 3) ? (rand() % 2 + 3) : (rand() % 4 + 3); // 3-4 pentru 3x3, 3-6 pentru 4x4

	// Asigură-te că nu se repetă pozițiile
	while (positions.size() < effects) {
		int row = rand() % size;
		int col = rand() % size;

		// Verifică dacă perechea este deja în vector
		std::pair<int, int> pos = { row, col };
		if (std::find(positions.begin(), positions.end(), pos) == positions.end()) {
			positions.push_back(pos);
		}
	}

	// Adaugă gropi (10% șansă pentru fiecare poziție afectată)
	for (auto& pos : positions) {
		if (rand() % 10 == 0) { // 10% șansă pentru groapă
			addHole(pos.first, pos.second);
			std::cout << "Special effect: Creating a hole at (" << pos.first << ", " << pos.second << ").\n";
		}
	}

	return positions;
}

void GameBoard::removeOpponentCardOverOwn(int row, int col, const Player& currentPlayer) {
	if (!isValidPosition(row, col)) {
		throw std::runtime_error("Invalid position on the board!");
	}

	if (!board[row][col].has_value()) {
		throw std::runtime_error("No card at the given position to remove!");
	}

	const Card& topCard = *board[row][col];
	if (topCard.owner == currentPlayer.name) {
		throw std::runtime_error("Cannot remove your own card!");
	}

	// Verificăm dacă există o carte proprie dedesubt
	bool hasOwnCardBelow = false;
	for (int i = row + 1; i < size; ++i) {
		if (board[i][col].has_value() && board[i][col]->owner == currentPlayer.name) {
			hasOwnCardBelow = true;
			break;
		}
	}

	if (!hasOwnCardBelow) {
		throw std::runtime_error("No own card below the opponent's card!");
	}

	// Eliminăm cartea de deasupra
	board[row][col].reset();
	std::cout << "Removed opponent's card at (" << row << ", " << col << ").\n";
}

void GameBoard::removeRowWithOwnCard(int row, const Player& currentPlayer) {
	if (row < 0 || row >= size) {
		throw std::runtime_error("Invalid row index!");
	}

	// Verifică dacă rândul îndeplinește condițiile
	int occupiedPositions = 0;
	bool hasOwnCard = false;

	for (int col = 0; col < size; ++col) {
		if (board[row][col].has_value()) {
			++occupiedPositions;
			if (board[row][col]->owner == currentPlayer.name) {
				hasOwnCard = true;
			}
		}
	}

	if (occupiedPositions < 3) {
		throw std::runtime_error("The row must occupy at least 3 positions!");
	}
	if (!hasOwnCard) {
		throw std::runtime_error("The row must contain at least one of your cards!");
	}

	// Elimină toate cărțile din rând
	for (int col = 0; col < size; ++col) {
		board[row][col].reset();
	}

	std::cout << "Removed all cards from row " << row << ".\n";
}

void GameBoard::destruction(Player& opponent) {
	if (opponent.hand.empty()) {
		throw std::runtime_error("Opponent has no cards to destroy!");
	}
	opponent.hand.pop_back();
	std::cout << "Destruction activated: The last card of the opponent is eliminated.\n";
}

void GameBoard::flames(Player& opponent, Player& currentPlayer) {
	for (auto& row : board) {
		for (auto& cell : row) {
			if (cell && cell->isIllusion && cell->owner == opponent.name) {
				cell->isIllusion = false; // Dezvăluie iluzia
				std::cout << "Illusion revealed!\n";
				break;
			}
		}
	}

	int row, col;
	std::cout << "Enter the position to play a card (row and col): ";
	std::cin >> row >> col;

	if (!isValidPosition(row, col) || board[row][col]) {
		throw std::runtime_error("Invalid position to play a card.");
	}

	currentPlayer.addCard(Card(1));
	board[row][col] = currentPlayer.hand.back(); // Joacă o carte
	currentPlayer.hand.pop_back();
	std::cout << "Card placed at (" << row << ", " << col << ").\n";
}

void GameBoard::lava(int number) {
	for (auto& row : board) {
		for (auto& cell : row) {
			if (cell && cell->value == number) {
				Player* owner = (cell->owner == "Player 1") ? &player1 : &player2;
				owner->addCard(*cell);
				cell.reset();
			}
		}
	}
	std::cout << "Lava activated: Cards with number " << number << " returned to owners' hands.\n";
}

void GameBoard::fromAshes(Player& currentPlayer, Card card) {
	currentPlayer.addCard(card);
	std::cout << "From Ashes activated: Card restored to " << currentPlayer.name << "'s hand.\n";
}

bool GameBoard::isCardCoveredByOpponent(int row, int col, const Player& player) const {
	if (!isValidPosition(row, col) || !board[row][col].has_value()) {
		return false;
	}

	// Verifică dacă proprietarul cărții de deasupra este adversarul
	return board[row][col]->owner != player.name;
}


int GameBoard::calculateScore(const Player& player) const
{
	int score = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j].has_value() && board[i][j]->owner == player.name) {
				score += board[i][j]->isIllusion ? 1 : board[i][j]->value;
			}
		}
	}
	return score;
}

bool GameBoard::checkIllusionRule(int row, int col, Player& opponent) {
	if (!isValidPosition(row, col)) {
		throw std::runtime_error("Invalid position on the board!");
	}

	if (!board[row][col].has_value()) {
		throw std::runtime_error("No card at the given position!");
	}

	// Obține o referință modificabilă la carte
	auto& placedCard = board[row][col].value();

	if (!placedCard.isIllusion) {
		return false; // Nu este o iluzie
	}

	// Întoarce cartea iluzie cu fața în sus și verifică regulile
	std::cout << "Illusion revealed at (" << row << ", " << col << ")!\n";
	placedCard.isIllusion = false; // Iluzia devine o carte normală

	// Verifică dacă oponentul încearcă să acopere iluzia
	if (!opponent.hand.empty()) {
		// Găsește o carte din mâna oponentului
		int cardIndex;
		std::cout << "Select a card from your hand to attempt covering the illusion (1-"
			<< opponent.hand.size() << "): ";
		std::cin >> cardIndex;
		cardIndex -= 1; // Ajustează indexul pentru vector

		if (cardIndex < 0 || cardIndex >= opponent.hand.size()) {
			throw std::runtime_error("Invalid card index!");
		}

		const Card& opponentCard = opponent.hand[cardIndex];

		if (opponentCard.value <= placedCard.value) {
			// Cartea oponentului este eliminată
			std::cout << "Opponent's card (value " << opponentCard.value
				<< ") is eliminated!\n";
			opponent.removeCard(cardIndex); // Elimină cartea din mână
			return true; // Oponentul își încheie tura
		}
		else {
			std::cout << "Opponent successfully covered the illusion with card of value "
				<< opponentCard.value << ".\n";
			board[row][col] = opponentCard; // Plasează cartea oponentului pe tablă
			opponent.removeCard(cardIndex); // Elimină cartea din mână
		}
	}

	return true; // Oponentul nu poate continua tura
}
