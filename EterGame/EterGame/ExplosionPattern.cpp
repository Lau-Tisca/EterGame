//ExplosionPattern.cpp

#include "ExplosionPattern.h"
#include <vector>
#include <random>
#include <iostream>
#include <utility> // pentru std::pair
#include <algorithm> // pentru std::find
#include <cstdlib>   // pentru rand()
#include <ctime>     // pentru srand()

ExplosionPattern::ExplosionPattern(int gridSize) {
    generateExplosion(gridSize);
}

ExplosionPattern::ExplosionPattern(std::vector<ExplosionTile> tiles) {
    affectedTiles = std::move(tiles);
}

const std::vector<ExplosionTile>& ExplosionPattern::getTiles() const {
    return affectedTiles;
}

std::vector<ExplosionTile> ExplosionPattern::generateExplosionPattern(int gridSize, int& holeCount)
{
    return std::vector<ExplosionTile>();
}

void ExplosionPattern::generateExplosion(int gridSize) {
    affectedTiles.clear();
    std::vector<std::pair<int, int>> possiblePositions;
    for (int i = 0; i < gridSize; ++i)
        for (int j = 0; j < gridSize; ++j)
            possiblePositions.emplace_back(i, j);

    std::shuffle(possiblePositions.begin(), possiblePositions.end(), std::mt19937(std::random_device{}()));

    int numEffects = (gridSize == 3) ? rand() % 3 + 2 : rand() % 4 + 3;
    bool hasHole = false;
    for (int i = 0; i < numEffects; ++i) {
        ExplosionEffect effect;
        if (!hasHole || rand() % 10 == 0) {
            effect = ExplosionEffect::CreateHole;
            hasHole = true;
        }
        else {
            effect = (rand() % 2 == 0) ? ExplosionEffect::RemoveCard : ExplosionEffect::ReturnToHand;
        }
        affectedTiles.push_back({ possiblePositions[i].first, possiblePositions[i].second, effect });
    }
}

void ExplosionPattern::applyExplosion(GameBoard& board, int centerRow, int centerCol) {
    for (const auto& effect : affectedTiles) {
        int affectedRow = centerRow + effect.x - 1;
        int affectedCol = centerCol + effect.y - 1;

        if (!board.isValidPosition(affectedRow, affectedCol, 0))
            continue;

        if (board.isSpaceEmpty(affectedRow, affectedCol))
            continue;

        switch (effect.effect) {
        case ExplosionEffect::RemoveCard:
            board.removeCard(affectedRow, affectedCol);
            break;
        case ExplosionEffect::ReturnToHand:
            board.returnCardToPlayer(affectedRow, affectedCol);
            break;
        case ExplosionEffect::CreateHole:
            board.createHole(affectedRow, affectedCol);
            break;
        }
    }
}


void ExplosionPattern::rotatePattern(std::vector<std::pair<int, int>>& pattern, int size) {
    for (auto& pos : pattern) {
        int oldX = pos.first;
        int oldY = pos.second;
        pos.first = oldY;
        pos.second = size - 1 - oldX;
    }
}